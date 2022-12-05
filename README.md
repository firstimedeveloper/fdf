# fdf
42 graphics project

<img src="https://user-images.githubusercontent.com/8170405/205611357-39e5f82c-8075-4305-ba59-aaf195dcd08c.gif" width="50%">


This is an intro to graphics project done at 42 Seoul using the minilibx graphics libriary.

This program outputs an isometric projection of a 3d 'mesh' map
given an input of a text file with a .fdf file extension (it's a plain old text file).

In the textfile, there is a grid of numbers. The position of the numbers corresponds to the (x, y) position and the numbers themselves corresponds to the z-axis.

For example:

input: 

```
$cat test_maps/42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

output:
<img src="https://user-images.githubusercontent.com/8170405/205606740-b1a53afb-5a2a-44c7-8d12-fcb1e9645c63.jpg" width="50%">

The program:
```
make

# ./fdf [path_to_fdf_file_containing_map_information]
./fdf test_maps/pyramide.fdf
```
<img src="https://user-images.githubusercontent.com/8170405/205606198-8032cddc-db11-4f3f-aa33-f25ee7a28573.jpg" width="50%">

### As a bonus

Using the WASD keys will move the camera,
- -/+ keys will zoom in and out,
- </> keys will amplify the z-axis (the numbers in the text file)
- Q/E, LEFT/RIGHT, UP/DOWN keys will rotate the image along the x,y,z axis
- The r key will toggle between isometric and parallel projection 

https://user-images.githubusercontent.com/8170405/205611917-ac01836c-ad01-40d4-8477-4c01318199b5.mov
