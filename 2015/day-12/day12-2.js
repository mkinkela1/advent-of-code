const fs = require("fs");

const inputFilePath = "input.txt";
const inputLines = eval(fs.readFileSync(inputFilePath));

Object.defineProperty(Object.prototype, "isObject", {
  value: function () {
    return this.constructor === Object;
  },
  enumerable: false,
});

function removeRed(key, value) {
  const hasRed = Object.keys(this[key]).some((k) => this[key][k] === "red");

  if (this[key].isObject() && hasRed) {
    return;
  }
  return value;
}

const str = JSON.stringify(JSON.parse(inputLines), removeRed);

const sum = str.match(/-?\d+/g)?.reduce((a, b) => a + parseInt(b), 0);

console.log("Part 2: ", sum);
