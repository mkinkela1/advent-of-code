class State {
    constructor(name, type, outputs) {
        this.name = name;
        this.type = type;
        this.outputs = outputs;
        if(type === '%')
            this.memory = "off";
        else 
            this.memory = {};
    }
}

import * as fs from "fs";

const modules = {};
let broadcastTargets = [];

const inputFilePath = "input.txt";
fs
  .readFileSync(inputFilePath, "utf-8")
  .split("\n")
  .filter(Boolean)
  .forEach((line) => {
    const [source, target] = line.split(" -> ");
    const targets = target.split(", ");

    if(source ==="broadcaster") {
        broadcastTargets = targets;
    } else {
        const type = source[0];
        const name = source.substring(1);

        modules[name] = new State(name, type, targets);
    }
  });

  
  
for(const name in modules) {
    for(const output of modules[name].outputs) {
        if(modules[output] && modules[output].type === '&') {
            modules[output].memory[name] = "lo";
        }
    }
}

let lo = 0, hi = 0;

for(let i = 0; i < 1000; ++i) {
    ++lo;

    const q = [];
    for(const target of broadcastTargets) {
        q.push(["broadcaster", target, "lo"]);
    }

    while(q.length > 0) {
        const [source, target, pulse] = q.shift();

        if(pulse === "hi")
            ++hi;
        else 
            ++lo;   

        if(!modules[target])
            continue;

        if(modules[target].type === '%') {
            if(pulse === "lo") {
                modules[target].memory = modules[target].memory === "off" ? "on" : "off";
                const outgoing = modules[target].memory === "on" ? "hi" : "lo";
                for(const output of modules[target].outputs) {
                    q.push([target, output, outgoing]);
                }
            }
        } else {
            modules[target].memory[source] = pulse;

            let areAllHigh = true;
            for(const input of Object.values(modules[target].memory)) {
                if(input === "lo") {
                    areAllHigh = false;
                    break;
                }
            }

            const outgoing = areAllHigh ? "lo" : "hi";
            
            for(const output of modules[target].outputs) {
                q.push([target, output, outgoing]);
            }
        }
    }
}

console.log({lo, hi});
console.log(lo*hi);

const nums = prevOfPrevOfRx.map((name) => check(Object.keys(name)[0]));
console.log(nums);

const gcd = (a, b) => !b ? a : gcd(b, a % b);

const lcm = (a, b) => a * (b / gcd(a,b));

console.log(nums.reduce(lcm, 1));