# Roadmap
The following roadmap is conceptional and consoider it now like a draft, this project is in an early stage and under heavy development, so the milestones will shift quite often.

## Active
I will try to keep this roadmap up to date, but it is not a promise.
### 2024 Q1
```mermaid
gantt
title 2024 Q1
excludes weekdays 2024-01-01

section M3<br>Base II<br>Core II
Application II                 :crit,    m1, 2024-01-07, 1M
Devices II, System II          :crit,    m2, 2024-01-07, 1M
Events                         :crit,    m3, after m2, 1M
```

## Overview
This is my wish, what I want to achieve with this project. It is a long way to go, but I am confident that I can make it.

```mermaid
gantt
title 2024 Q1
excludes weekdays 2024-01-01

section Base
Base                    :active,    m1, 2024-01-01, 1M

section Core
Core                    :active,    m1, 2024-01-01, 3M

section Graphics
Prisma (Renderer)       :           m2, 2024-02-01, 6M
section Graphics
Sculpt (Mesh Renderer)  :           m4, 2024-03-15, 6M
Aurora (UI Renderer)    :           m5, 2024-05-15, 6M

section Physics
Flux (Physics)          :           m6, after m5, 6M

section Animation
Wave (Animations)       :           m7, after m6, 6M
```


## History
#### 2024
```mermaid
gantt
title 2024 Q1
excludes weekdays 2024-01-01

section M1<br>Foundation I
Preparation     :crit, done,    m1.0, 2024-01-01, 2d
Architecture    :crit, done,    m1.0, 2024-01-02, 3d
Structure       :crit, done,    m1.1, 2024-01-03, 5d

section M2<br>Base I<br>Core I
Application I                   :crit, done,    m2.0, 2024-01-02, 4d
Platform, Types I, Extensions   :crit, done,    m2.1, 2024-01-03, 2d
Debug I                         :crit, done,    m2.2, 2024-01-04, 1d
Logger                          :crit, done,    m3.2, 2024-01-04, 1d
Mathematics I                   :crit, done,    m2.3, 2024-01-05, 2d
3rd-Party I                     :crit, done,    m2.4, 2024-01-05, 2d
System I                        :crit, done,    m2.5, 2024-01-06, 1d
Devices I                       :crit, done,    m2.6, 2024-01-06, 2d
Utils                           :crit, done,    m3.3, 2024-01-07, 1d
```
