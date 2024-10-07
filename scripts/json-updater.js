/* Modify keys in the package.json file
Usage:   `libMVRgdtf$ >node scripts/json-updater.js --key value --key2 value2 ...`
Example: `libMVRgdtf$ >node scripts/json-updater.js --name @mvr/lib-windows`
*/

const fs = require('fs');
const path = require('path');

const ARRAY_KEYS = ["files", "os"];

class PackageJSONManager {
    constructor() {
        this.filePath = path.join('package.json')
        this.packageJson = JSON.parse(fs.readFileSync(this.filePath, 'utf8'));
    }

    updateKey(key, value) {
        if (!key || !value) return;
        this.packageJson[key] = ARRAY_KEYS.includes(key)
            ? value.split(',')
            : value
    }

    save() {
        fs.writeFileSync(this.filePath, JSON.stringify(this.packageJson, null, 4) + '\n');
    }
}

const manager = new PackageJSONManager();
process.argv.forEach((key, index) => {
    if (key.startsWith('--')) {
        manager.updateKey(key.substring(2), process.argv[index + 1]);
    }
})
manager.save()
