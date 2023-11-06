import * as fs from "fs";

const inputFilePath = "input.txt";
const inputLines = fs
  .readFileSync(inputFilePath, "utf-8")
  .split("\n")
  .filter(Boolean)
  .map(eval);

function compare(a: any, b: any): number {
  if (!a && a !== 0) return 1;
  if (!b && b !== 0) return -1;

  if (Array.isArray(a) || Array.isArray(b)) {
    const left = Array.isArray(a) ? a : [a];
    const right = Array.isArray(b) ? b : [b];

    return compareArrays(left, right);
  }

  if (a == b) return 0;
  return a < b ? 1 : -1;
}

function compareArrays(a: any, b: any): number {
  const len = Math.max(a.length, b.length);

  for (let i = 0; i < len; i++) {
    const cmp = compare(a[i], b[i]);
    if (cmp !== 0) return cmp;
  }

  return 0;
}

let part1 = 0;
for (let i = 0, pair = 1; i < inputLines.length; i += 2, ++pair) {
  if (compare(inputLines[i], inputLines[i + 1]) === 1) part1 += pair;
}

console.log("Part 1:", part1);

inputLines.push([[2]]);
inputLines.push([[6]]);

inputLines.sort(compare);
inputLines.reverse();

const inputLinesString = inputLines.map((line) => JSON.stringify(line));

const id1 = inputLinesString.indexOf("[[2]]") + 1;
const id2 = inputLinesString.indexOf("[[6]]") + 1;

console.log("Part 2:", id1 * id2);
