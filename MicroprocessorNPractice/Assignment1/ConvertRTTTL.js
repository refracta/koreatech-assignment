let target = process.argv.slice(2).join(" ");
let[name, setting, data] = target.split(":").map(e => e.trim());
data = data.toLowerCase();
setting = Object.assign(...setting.split(",").map(e => Object.fromEntries([e.trim().split('=')])));
data = data.split(',').map(e => e.trim().replace('c#', 'C').replace('d#', 'D').replace('f#', 'F').replace('g#', 'G').replace('a#', 'A').split(''));
data = data.map(e => {
    let d = e.filter(e=>e==='.').length;
    e = e.filter(e=>e!=='.');
    if (!isNaN(e[0]) && !isNaN(e[1])) {
        e = [parseInt(e[0] + e[1]), ...e.slice(2)];
    }
    let b = parseInt(setting.b);
    let o = parseInt(setting.o);
    let v;
    if (e.length == 1) {
        v = e[0];
    } else if (e.length == 2) {
        if (isNaN(e[0])) {
            v = e[0];
            o = parseInt(e[1]);
        } else {
            b = b * parseInt(e[0]) / 4;
            v = e[1];
        }
    } else if (e.length == 3) {
        b = b * parseInt(e[0]) / 4;
        v = e[1];
        o = parseInt(e[2]);
    }
    let base = 1;
    let ratio = 1;
    for (let i = 0; i < d; i++) {
        base /= 2;
        ratio += base;
    }
    b /= ratio;
    b = Math.round(b);
    return {
        b,
        v,
        o
    };
});
console.log(data);
data = data.map((e, i, a) => {
    if (i == 0) {
        return `${e.o}S${e.b}${e.v}`;
    } else {
        let pe = a[i - 1];
        let sb = e.v;
        if (pe.b != e.b) {
            sb = 'S' + e.b + sb;
        }
        if (pe.o != e.o) {
            sb = e.o + sb;
        }
		return sb;
    }
}).join('');
console.log('Name: ' + name);
console.log('Setting: ' + JSON.stringify(setting));
console.log('Data: ' + data);