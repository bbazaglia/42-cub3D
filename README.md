<h1 align="center">
	🎲 cub3D
</h1>

## 💡 About the project

This project is inspired by the world-famous Wolfenstein 3D game, which was the first "First Person Shooter" ever. 
The goal is to make a dynamic view inside a maze using the ray-casting algorithm.

## 📝 Requirements

• Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).

• Your program must be able to set the floor and ceiling colors to two different ones.

• Your program must take as a first argument a scene description file with the .cub extension.
  ◦ The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
  ◦ The map must be closed/surrounded by walls, if not the program must return an error.
  ◦ Except for the map content, each type of element can be separated by one or more empty line(s).
  ◦ Except for the map content which always has to be the last, each type of element can be set in any order in the file.
  ◦ Except for the map, each type of information from an element can be separated by one or more space(s).
  ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.
  ◦ Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order

• If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.

## 📋 Testing

To compile, go to the project path and run:

```shell
$ make 
```

Then, execute the program with the map chosen:

```shell
$ ./cub3D maps/valid/subject.cub
```

## 🕹️ Playing

  ◦ The left and right arrow keys of the keyboard allow you to look left and right in the maze.
  ◦ The W, A, S, and D keys allow you to move the point of view through the maze.
  ◦ Pressing ESC close the window and quit the program.

Disclaimer: The main purpose of this repository is to expose my code and help other students to understand what was done in each function. Therefore, this work should be used for academic reasons, by those who aim to learn, and not merely copy.
