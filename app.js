import { getString, getFunction } from './index.js';

const state = { running: false }

export function print(ptr) {
  console.log(getString(ptr));
}

export function init() { }

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

function toggleMaximized() {
  state.win.classList.toggle('maximized');
  if (state.win.classList.contains('maximized')) {
    state.canvas.width = window.innerWidth;
    state.canvas.height = window.innerHeight - 28;
  } else {
    state.canvas.width = state.width;
    state.canvas.height = state.height;
  }
}

export function createWindow(ptr, width, height) {
  state.width = width;
  state.height = height;
  document.title = getString(ptr);
  const template = document.querySelector('#window-template');
  state.win = template.content.cloneNode(true).firstElementChild;
  state.win.querySelector('.window-title').textContent = getString(ptr);
  state.win.style.width = `${width}px`;
  state.win.style.height = `${height + 28}px`;
  state.canvas = state.win.querySelector('canvas');
  state.canvas.width = width;
  state.canvas.height = height;
  state.ctx = state.canvas.getContext('2d');
  document.body.appendChild(state.win);
  state.win.querySelector('.traffic-light.close').addEventListener('click', () => {
    state.running = false;
  });
  state.win.querySelector('.traffic-light.minimize').addEventListener('click', () => {
    console.log('minimize');
  });
  state.win.querySelector('.traffic-light.maximize').addEventListener('click', toggleMaximized);
  state.win.querySelector('.window-titlebar').addEventListener('dblclick', toggleMaximized);
}

export function setDrawColor(r, g, b, a) {
  state.ctx.fillStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
  state.ctx.strokeStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
}

export function clearScreen() {
  state.ctx.fillRect(0, 0, state.canvas.width, state.canvas.height);
}

export function drawCircle(x, y, radius) {
  state.ctx.beginPath();
  state.ctx.arc(x, y, radius, 0, 2 * Math.PI);
  state.ctx.stroke();
}

export function drawLine(x1, y1, x2, y2) {
  state.ctx.beginPath();
  state.ctx.moveTo(x1, y1);
  state.ctx.lineTo(x2, y2);
  state.ctx.stroke();
}

export function destroyWindow() {
  console.log('destroyWindow');
  state.win.remove();
}

export function quit() {
  state.running = false;
}

export function setOnMouseMove(onMouseMovePtr) {
  state.canvas.addEventListener('mousemove', e => {
    let rect = state.canvas.getBoundingClientRect();
    let x = e.clientX - rect.left;
    let y = e.clientY - rect.top;
    getFunction(onMouseMovePtr)(x, y);
  });
}
