import * as env from './app.js';

let wasmInstance;
let memory;

export function getString(ptr) {
  const memoryBuffer = new Uint8Array(memory.buffer);
  let length = 0;
  while (memoryBuffer[ptr + length] !== 0) {
    length++;
  }
  const bytes = new Uint8Array(memory.buffer, ptr, length);
  return new TextDecoder('utf8').decode(bytes);
}

export function getFunction(ptr) {
  return wasmInstance.exports.__indirect_function_table.get(ptr);
}

(async function main() {
  const response = await fetch('app.wasm');
  const bytes = await response.arrayBuffer();
  const { instance } = await WebAssembly.instantiate(bytes, { env });
  wasmInstance = instance;
  memory = instance.exports.memory;
  instance.exports.start();
})().catch(console.error);
