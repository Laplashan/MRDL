<header>

<!--
  <<< Author notes: Course header >>>
  Include a 1280×640 image, course title in sentence case, and a concise description in emphasis.
  In your repository settings: enable template repository, add your 1280×640 social image, auto delete head branches.
  Add your open source license, GitHub uses MIT license.
-->

# MRDL V0.2

_Tools, documentation and background of our datalogger._

</header>

<!--
  <<< Author notes: Step 1 >>>
  Choose 3-5 steps for your course.
  The first step is always the hardest, so pick something easy!
  Link to docs.github.com for further explanations.
  Encourage users to open new tabs for steps!
-->

## Introduction

_Welcome everyone_

MRDL was born from the necessity of getting a better undarstanding of the dynamics of our car. The motivation behind this repository is an exploration into the world of DIY electronics, the end goal being to create a functional prototype that can be permanently mounted on our MR23C.
The data logging system consists of 3 key aspects:

Firmware, this program is flashed onto the micro-controller so as to control its general operation and communicate with the server software.

Server software, this program exposes various API endpoints which handle hardware registration, configuration and telemetry.

Client software, this program is the source code for a web based interface for hardware reporting and configuration. (Currently using Blynk)

## Objective and needs (Constantly updating)

To get a better understanding of our car we need to be able to read data from various sectors, wich can include temperature, speed, position, acceleration, impacts, etc.
In this section, we´ll add a quick list mencioning the key spots to get data from, and what sensor/implement can be used to get that data as well as if its covered or not.

1. Speed | GPS sensor | Status: Completed. | Mounted anywhere on the car.
     ![speed](/images/speedgraphs.jpg)
2. Position tracking | GPS sensor | Status: Partially completed (Issues w/ Blynk cloud) | Mounted anywhere on the car.
3. Engine RPM | Sensing Coil | Status: 50% completed | Mounted arround the sparkplug cable of the engine.
4. Suspension shock dynamics | Unknown | Status: 0% | -
5. Reductor temp. | Thermocouple XS 168 or similar | Status: Partially completed, prog. completed, sensor unmounted | Bolted directly on the reductor.


Get help: [Post in our discussion board](https://github.com/orgs/skills/discussions/categories/introduction-to-github) &bull; [Review the GitHub status page](https://www.githubstatus.com/)

&copy; 2024 GitHub &bull; [Code of Conduct](https://www.contributor-covenant.org/version/2/1/code_of_conduct/code_of_conduct.md) &bull; [MIT License](https://gh.io/mit)

</footer>
