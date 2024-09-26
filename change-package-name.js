const fs = require('fs');

class PackageJSONManager {
    constructor() {
        this.packageJson = JSON.parse(fs.readFileSync('package.json', 'utf8'));
    }

    updateKey(key, value) {
        if (!key || !value) return;
        this.packageJson[key] = value;
    }

    save() {
        fs.writeFileSync('package.json', JSON.stringify(this.packageJson, null, 4) + '\n');
    }
}

const manager = new PackageJSONManager();
process.argv.forEach((key, index) => {
    if (key.startsWith('--')) {
        manager.updateKey(key.substring(2), process.argv[index + 1]);
    }
})
manager.save()