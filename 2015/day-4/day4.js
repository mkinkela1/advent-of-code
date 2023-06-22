const {createHash} = require("node:crypto");

const input1 = "iwrupvqb";
let part1solution = 1, part2Solution = 1;

function hashText(content, algo = 'md5') {

  const hashFunc = createHash(algo);
  hashFunc.update(content);

  return hashFunc.digest('hex');
}

function solution(part, startsWith) {

    let idx = 1;

    while(true) {

        if(hashText(input1+idx).toString().startsWith(startsWith)) {
            console.log(`Part ${part}: ${idx}`);
            return;
        }
    
        ++idx;
    }
}

solution(1, "00000");
solution(2, "000000");