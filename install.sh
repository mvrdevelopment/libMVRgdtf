export PKG_V=$(node -p "require('./package.json').version")
export OS=$(node -p process.platform)

if npm show @mvrdevelopment/lib-gdtf-$OS@$PKG_V > /dev/null 2>&1; then
    npm install --save --save-exact @mvrdevelopment/lib-gdtf-$OS@$PKG_V
else
    echo "@mvrdevelopment/lib-gdtf-$OS@$PKG_V is not available on npm."
fi
