# Concept
This is the main concept of the project, which delivers a good overview about the inner workings.

### Architecture
```mermaid
classDiagram
    App <|-- Application

    Application --> Config
    Application --> Context
    Application --> Emmiter
    Application --> Renderer
    Application --> Window

    Context  --> Renderer
```
