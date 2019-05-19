// this is how we will require our module
const m = require('./bindings')
console.log(m)

const vec1 = new m.Vector(20, 10, 0)
console.log(vec1) // Vector { x: 20, y: 10, z: 0 }

const vec2 = new m.Vector(0, 0, 0)
vec2.x = 30
vec2.z = 100
console.log(vec2) // Vector { x: 30, y: 0, z: 100 }

const vecSum = vec1.add(vec2)
console.log(vecSum) // Vector { x: 50, y: 10, z: 100 }