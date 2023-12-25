import * as fs from "fs";

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

let prevOfRx = [];
for(const name in modules) {
    for(const output of modules[name].outputs) {
        if(output === "rx") {
            prevOfRx.push(name);
        }
    }
}

let prevOfPrevOfRx = [];
for(const prev of prevOfRx) {
    for(const name in modules) {
        for(const output of modules[name].outputs) {
            if(output === prev) {
                prevOfPrevOfRx.push(name);
            }
        }
    }
}

const nums = {};
for(const name of prevOfPrevOfRx) {
    nums[name] = 0;
}
const cycleLengths = {};

const gcd = (a, b) => {
    if(!b)
        return a;
    return gcd(b, a % b);
}

const lcm = (a, b) => {
    return a * b / gcd(a, b);
}

let ret = 0;

while(true) {

    ++ret;
    const q = [];
    for(const target of broadcastTargets) {
        q.push(["broadcaster", target, "lo"]);
    }

    while(q.length > 0) {
        const [source, target, pulse] = q.shift();

        if(!modules[target])
            continue;
        

        if(prevOfRx.includes(target) && pulse === "hi") {
            nums[source]++;

            if(!cycleLengths[source]) {
                cycleLengths[source] = ret;
            }

            let isEverySeen = true;
            for(const name in nums) {
                if(nums[name] === 0) {
                    isEverySeen = false;
                    break;
                }
            }

            if(isEverySeen) {
                let x = 1;
                for(const name in cycleLengths) {
                    x = lcm(x, cycleLengths[name]);
                }
                console.log(x);

                process.exit(0);
            }
        }

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


