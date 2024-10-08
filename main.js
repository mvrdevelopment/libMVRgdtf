const package = [
    "@mvrdevelopment/lib-gdtf-win32",
    "@mvrdevelopment/lib-gdtf-linux",
    "@mvrdevelopment/lib-gdtf-darwin"
].find(entry => {
    try {
        return require(entry)
    } catch (e) {
    }
})

module.exports = package