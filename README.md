# Circle Intersection

I created this project while learning about [inverse kinematics](https://en.wikipedia.org/wiki/Inverse_kinematics). Circle intersection is a fundamental concept in inverse kinematics.

This project uses a custom rendering API that supports both a native SDL2 target and a WebAssembly target. This enables the same codebase to be used for both native and web platforms.

## Requirements

- SDL2
- SDL2_gfx

## Compile and Run Natively (using SDL2)

To compile and run the project natively:

```bash
make
```

## Compile to WebAssembly (using JS Canvas API)

To compile the project to WebAssembly:

```bash
make wasm
```

After compiling, start a local server inside the `web` folder and open the page in your browser.

## Contributing

If you **have a question**, **found a bug** or want to **propose a feature**, have a look at [the issues page](https://github.com/pepebecker/circle-intersection/issues).
