import { getString, getFunction } from './index.js';

const state = { running: false }

export function print(ptr) {
  console.log(getString(ptr));
}

export function getRandom() {
  return Math.random();
}

export function init() {
  state.canvas = document.createElement('canvas');
  document.body.appendChild(state.canvas);
  state.ctx = state.canvas.getContext('2d');
}

let lastUpdate = Date.now();
const gameLoop = (loop, onComplete, time = 0) => {
  if (state.running) {
    requestAnimationFrame(() => gameLoop(loop, onComplete, time));
    let now = Date.now();
    let dt = now - lastUpdate;
    lastUpdate = now;
    loop(dt);
  } else {
    onComplete();
  }
}

export function runGameLoop(gameLoopPtr, onCompletePtr) {
  state.running = true;
  gameLoop(getFunction(gameLoopPtr), getFunction(onCompletePtr));
}

export function createWindow(ptr, width, height) {
  document.title = getString(ptr);
  state.canvas.width = width;
  state.canvas.height = height;
}

export function setDrawColor(r, g, b, a) {
  state.ctx.fillStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
  state.ctx.strokeStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
}

export function clearScreen() {
  state.ctx.fillRect(0, 0, state.canvas.width, state.canvas.height);
}

export function drawRect(x, y, width, height) {
  state.ctx.strokeRect(x, y, width, height);
}

export function fillRect(x, y, width, height) {
  state.ctx.fillRect(x, y, width, height);
}

export function drawCircle(x, y, radius) {
  state.ctx.beginPath();
  state.ctx.arc(x, y, radius, 0, 2 * Math.PI);
  state.ctx.stroke();
}

export function fillCircle(x, y, radius) {
  state.ctx.beginPath();
  state.ctx.arc(x, y, radius, 0, 2 * Math.PI);
  state.ctx.fill();
}

export function drawLine(x1, y1, x2, y2) {
  state.ctx.beginPath();
  state.ctx.moveTo(x1, y1);
  state.ctx.lineTo(x2, y2);
  state.ctx.stroke();
}

export function destroyWindow() {
  state.canvas.remove();
}

export function quit() {
  state.running = false;
}

export function setOnMouseMove(onMouseMovePtr) {
  window.addEventListener('mousemove', e => {
    let rect = state.canvas.getBoundingClientRect();
    let x = e.clientX - rect.left;
    let y = e.clientY - rect.top;
    getFunction(onMouseMovePtr)(x, y);
  });
}
