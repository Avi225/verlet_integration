<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Avi225/verlet_integration">
    <img src="res/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Verlet Integration</h3>

  <p align="center">
    Simple cloth physics engine written in C++ with SDL2
    <br>
    <a href="https://github.com/Avi225/verlet_integration/issues">Report Bug</a>
    ·
    <a href="https://github.com/Avi225/verlet_integration/issues">Request Feature</a>
  </p>
</div>

https://github.com/Avi225/verlet_integration/assets/61160595/ace7b294-f665-4ce9-b4c8-8d3f9437254d

## Building
1. Clone the repo
2. Requires SDL2, SDL2_image and SDL2_ttf
3. Example build command with mingw64:
   ```sh
   g++ -c src/*.cpp -std=c++14 -Wall -m64 -I include -I C:/SDL2-w64/include && g++ *.o -o bin/release/cloth src/icon.res -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
   ```



<!-- ROADMAP -->
## Goals

- [ ] Compression and Stretch 
- [ ] Antialiasing
- [ ] OpenGL rendering

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/Avi225/verlet_integration/forks
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/Avi225/verlet_integration/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/Avi225/verlet_integration/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/Avi225/verlet_integration/blob/main/LICENSE
