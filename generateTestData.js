let vector = [];
let matrix = [];

let min = 0;
let max = 10;

let m = 64;
let n = 5;

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

for (let i = 0; i < n; i++) {
  vector[i] = getRandomInt(min, max);
}

console.log("vector\n" + vector);

for (let row = 0; row < m; row++) {
  matrix[row] = [];
  for (let col = 0; col < n; col++) {
    matrix[row][col] = getRandomInt(min, max);
  }
}

console.log("matrix\n" + JSON.stringify(matrix));

let results = [];
for (let row = 0; row < m; row++) {
  let currRow = matrix[row];
  results[row] = 0;
  for (let col = 0; col < n; col++) {
    results[row] += currRow[col] * vector[col];
  }
  console.log(currRow + " " + results[row]);
}

console.log("Results\n" + results);

let matrixString = "";
matrix.forEach(arr => {
  arr.forEach(num => {
    matrixString += num + " ";
  });
});

let vectorString = "";
vector.forEach(num => {
  vectorString += num + " "
})

console.log("Paste input");
console.log(n + " " + matrixString + " " + vectorString);

let outputString = "";
results.forEach(num => {
  outputString += num + "\n";
})
outputString += "\n";

console.log("Paste output");
console.log(outputString);
