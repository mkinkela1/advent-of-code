const fs = require("fs");
const { createHash } = require("node:crypto");

const input = fs.readFileSync("./input.txt", "utf-8").trim();

function md5(content, algo = "md5") {
  const hashFunc = createHash(algo);
  hashFunc.update(content);

  return hashFunc.digest("hex");
}

const part1 = () => {
  let password = "";
  let index = 0;

  while (password.length < 8) {
    const hash = md5(input + index);

    if (hash.startsWith("00000")) {
      password += hash[5];
    }

    index++;
  }

  return password;
};

const part2 = () => {
  let password = Array(8).fill(null);
  let index = 0;

  while (password.includes(null)) {
    const hash = md5(input + index);

    if (hash.startsWith("00000")) {
      const position = parseInt(hash[5]);

      if (position < 8 && password[position] === null) {
        password[position] = hash[6];
      }
    }

    index++;
  }

  return password.join("");
};

console.log("Part 1:", part1());
console.log("Part 2:", part2());
