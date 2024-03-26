const fs = require('fs');
let files = fs.readdirSync('results').filter(e => e.endsWith('.txt'));
for (let file of files) {
    let text = fs.readFileSync(`results/${file}`, 'utf8');
    let lines = text.split('\n');
    let first = lines[0];
    let [tat, wt, rt] = first.split(/[:, ]/gi).filter(e => e && !isNaN(e)).map(e => parseFloat(e));
    let others = lines.slice(1);
    others = others.map(l => ',,,'+ l.replace(/ /gi, '').replace(/\t/g, ','));
    let csv = '\n' + others.join('\n');
    csv += `\nAverage_Turnaround_Time,Average_Waiting_Time,Average_Response_Time\n${tat},${wt},${rt}`
    fs.writeFileSync(`results/csv/${file.replace('.txt', '.csv')}`, csv, 'utf8');
    console.log(csv);
}