const fs = require("fs");
const path = require("path");
const { execSync } = require("child_process");

const buildDir = path.join(__dirname, "..", "build");

fs.rmSync(buildDir, {
    recursive: true,
    force: true
});

fs.mkdirSync(buildDir, {
    recursive: true
});

ensureLinuxPackages();

let osCMakeGeneratorParams = "";
if(process.platform == "win32")
{
    osCMakeGeneratorParams = `-G "Visual Studio 17 2022" -A x64 -DWIN_RUNTIME_LIB=-MT `;
}
execSync(`cmake .. ${osCMakeGeneratorParams} -DBUILD_MVR_XCHANGE=FALSE -DDONT_USE_XERCES_AS_XMLLIB=TRUE`,
{
    cwd: buildDir,
    stdio: "inherit"
});

execSync( 'cmake --build . --config Release',
{
    cwd: buildDir,
    stdio: "inherit"
});

function ensureLinuxPackages()
{
    if (process.platform !== "linux") return;

    const packages = [
        "build-essential",
        "uuid-dev"
    ];

    const missing = [];

    for (const pkg of packages) 
    {
        try
        {
            execSync(`dpkg -s ${pkg}`, {
                stdio: "ignore"
            });
        }
        catch
        {
            missing.push(pkg);
        }
    }

    if (missing.length > 0)
    {
        console.log(`Installing missing packages: ${missing.join(", ")}`);
        execSync("sudo apt-get update", {
            stdio: "inherit"
        });
        execSync(`sudo apt-get install -y ${missing.join(" ")}`,
        {
            stdio: "inherit"
        });
    }
}