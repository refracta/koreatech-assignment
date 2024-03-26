const fs = require('fs');
let files = fs.readdirSync('results').filter(e => e.endsWith('.txt'));
let csv = `Type,Average_Turnaround_Time,Average_Waiting_Time,Average_Response_Time\n`

for (let file of files) {
    let text = fs.readFileSync(`results/${file}`, 'utf8');
    let lines = text.split('\n');
    let first = lines[0];
    let [tat, wt, rt] = first.split(/[:, ]/gi).filter(e => e && !isNaN(e)).map(e => parseFloat(e));
    let others = lines.slice(1);
    others = others.map(l => ',,,' + l.replace(/ /gi, '').replace(/\t/g, ','));
    csv += `${file.replace('.txt', '')},${tat},${wt},${rt}\n`;
    console.log(csv);
}
fs.writeFileSync(`results/csv/final.csv`, csv, 'utf8');
