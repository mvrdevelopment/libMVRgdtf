export PKG_V=$(node -p "require('./package.json').version")
npm install --save --save-exact @mvrdevelopment/lib-gdtf-win32@$PKG_V @mvrdevelopment/lib-gdtf-linux@$PKG_V @mvrdevelopment/lib-gdtf-darwin@$PKG_V
