# Introduction

Edge detection by LoG filter

# Background

① Gradient The brightness change rate of object in image is detected to apply differential for getting slope it is called gradient in image processing especially. However, the data in each pixel is stored as discrete form itself, not as to continuous form so that it can not be applied to a sense of mathematical differential operation. Therefore, differential has approximated a difference between adjacent pixels. In here, we have a 2D image that will be applied both horizontal and vertical directions.

② Zero-crossing The Laplacian is typical method among second order derivative in edge detection. But this method has two edges that have conversely slope's sign due to the nature of the Laplacian. To eliminate one useless edge between two edges, we apply to zero-crossing method. ![graph](https://cloud.githubusercontent.com/assets/20148930/23981664/9fbe5cca-0a4b-11e7-9346-097eaf80a057.JPG)

# Result

![loginit](https://cloud.githubusercontent.com/assets/20148930/23981591/05044a96-0a4b-11e7-9bcd-42c0142d1b1d.png)

![logimplement](https://cloud.githubusercontent.com/assets/20148930/23981592/0505853c-0a4b-11e7-8f30-f8ac97eae442.png)

![logzerocrossing](https://cloud.githubusercontent.com/assets/20148930/23981594/08636366-0a4b-11e7-9a5b-183745d5766f.png)

# Reference

Laplacian of Gaussian / <http://fourier.eng.hmc.edu/e161/lectures/gradient/node8.html>

Laplacian of Gaussian / <https://softwarebydefault.com/tag/laplacian-of-gaussian/>

Laplacian of Gaussian / <http://www.ics.uci.edu/~majumder/DIP/classes/EdgeDetect.pdf>
