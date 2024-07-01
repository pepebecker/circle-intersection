const windowTitleBarHTML = `
  <div class="window-titlebar">
    <span class="traffic-lights">
      <div class="traffic-light close"></div>
      <div class="traffic-light minimize"></div>
      <div class="traffic-light maximize"></div>
    </span>
    <span class="window-title"></span>
  </div>
  <div class="window-content"></div>
`;

function createWindow(title, width, height) {
  const element = document.createElement('div');
  element.classList.add('window');
  element.innerHTML = windowTitleBarHTML;
  element.querySelector('.window-title').textContent = title;
  element.style.width = `${width}px`;
  element.style.height = `${height + 28}px`;
  document.body.appendChild(element);
  const ctx = {
    element,
    onClose() { },
    onMinimize() { },
    onResize() { },
    destroy() {
      element.remove();
    },
  };
  function onMaximize() {
    element.classList.toggle('maximized');
    if (element.classList.contains('maximized')) {
      ctx.onResize(window.innerWidth, window.innerHeight - 28);
    } else {
      ctx.onResize(width, height);
    }
  }
  element.querySelector('.traffic-light.close').addEventListener('click', () => ctx.onClose());
  element.querySelector('.traffic-light.minimize').addEventListener('click', () => ctx.onMinimize());
  element.querySelector('.traffic-light.maximize').addEventListener('click', onMaximize);
  element.querySelector('.window-titlebar').addEventListener('dblclick', onMaximize);
  prefetchImage('./win/icon-close.svg');
  prefetchImage('./win/icon-minimize.svg');
  prefetchImage('./win/icon-maximize.svg');
  return ctx;
}

function prefetchImage(url) {
  const img = new Image();
  img.src = url;
}

export const win = { createWindow };
