# My CodingTwo_FinalProject
Made in Open FrameWork  
If want to run on your personal computer, you need put the folder "codingTwoFinal" into the "\OF_v20220226_vs2017_release\apps\myApps\"  

# Space Adventure
-- Coding Two Final Project
## Video Link: https://youtu.be/i4iP35M4XV4
## Description:  
### (1)Story  
This is a greatly exciting space adventure, hoping everyone can have a nice minute in it.
At the beginning of the birth of all things, there were 4 running constellations setting at the each corner, which can be described like Two-parted, Three-parted, Six-parted and Serial groups. One day, they are combined by an anonymous power, then they orbiting the center of space, but still retain some own characteristics. Then many new planets born with smaller radius and they orbiting the four original constellations. As old principle goes, ”Any long-time cohesion will bring some , vice versa . ” Some interesting actions and dynamics happen after a great period aggregation. However, antimatter generate, which is uninvited guest and has a huge attraction to normal matter, so the matter-planets and antimatter-planets are closer, finally they disappeared......  

### (2)Technical Details  
The main technical points are: I. Elements’ positions and shapes rendering; II. 2D to 3D conversion; III. Mirror and copy-constructior; IV. Overall change and control of the animation process. Of course, there are many other technical details, but I do not need introduce them too much here.  
I. A lot of circles and spheres are used in this project, mainly because these shapes can well simulate the particles and planets in nature, and it has less edges and corners, which can bring a good sense of beauty. Furthermore, he positions of the elements can be set by functions such as x = cos() , y = sin(), etc.  
II. Using the built-in-OF camera EasyCam, it can be implemented well, and as long as the position and direction of the camera are preset with a good design, the connection between 2D and 3D is done, and after I let the camera begin to move with the time slowly; at the same time, it should be noted that the graphics made by draw functions in the 3D view must be spheres rather than circles, etc.  
III. The image is not generated from the beginning, nor is it directly mapped, because I think these are not free enough. I added a copy constructor to the class pathObj, newly opened up space (yes , it is deep copy) for the newly generated image instance, and reversed the z of the original instance.  
IV. The overall of the animation is controlled by the float t declared in advance and will develop by each frame time, and the method of “key frame” is used in this project.    

### (3)Extra State  
Since the music embedded is "Adventure Time" by Norwegian music maker Philter, I promise that this work will be never for any commercial use before any authorization.

## Info.
By GuanghanWu  
21032233  
G.wu0520211@arts.ac.uk  
