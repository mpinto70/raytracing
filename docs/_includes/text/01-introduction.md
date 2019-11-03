## Introduction

The idea of raytracing is to build an image based on a **camera**, a **field of view**, and the **rays** from the camera
to each point in the field of view. 

<p align="center">
<img src="assets/images/01-camera-field-of-view.svg">
</p>

Given a field of view with size $$W_{FoV} \times H_{FoV}$$ and an screen of size $$W_{scr} \times H_{scr}$$, it is 
necessary to send a ray from the camera to each point of the field of view divided by the dimensions of the screen and 
check the color that be filled in that position in the screen.

A ray is defined by its origin and its direction:

$$
\mathbf{p}(t) = \mathbf{A} + \mathbf{B}t \tag{1}
$$

<p align="center">
<img src="assets/images/02-ray.svg">
</p>

Initially, $$\mathbf{A}$$ is the camera position. To decide pixel color, it is necessary to determine if the ray hits an
object in the environment.

<p align="center">
<img src="assets/images/03-sphere.svg">
</p>

For a sphere, the hit point is determined by the equation:

$$
(\mathbf{p} - \mathbf{C}) \cdot (\mathbf{p} - \mathbf{C}) = R^2 \tag{2}
$$

From eq. 1:

$$
(\mathbf{A} + \mathbf{B}t - \mathbf{C}) \cdot (\mathbf{A} + \mathbf{B}t - \mathbf{C}) - R^2 = 0 \tag{3}
$$

Expanding and applying the [properties of dot product](https://en.wikipedia.org/wiki/Dot_product#Properties):

$$
\underbrace{\mathbf{B} \cdot \mathbf{B}}_{a}t^2
+ \underbrace{2\mathbf{B} \cdot (\mathbf{A} - \mathbf{C})}_{b}t
+ \underbrace{(\mathbf{A} - \mathbf{C}) \cdot (\mathbf{A} - \mathbf{C}) - R^2}_{c} = 0 \tag{4}
$$

Solving the quadratic polynomial on $$t$$ will give us the values of $$t$$ that satisfies the equation:

$$
b^2 - 4ac 
\begin{cases}
< 0, & \textsf{no root, not crossing} \\
= 0, & \textsf{one root, touches tangentially} \\
< 0, & \textsf{two roots, crosses the sphere} \\
\end{cases} \tag{5}
$$

<p align="center">
<img src="assets/images/04-sphere-and-rays.svg">
</p>

That way, the values for $$t$$ that satisfies eq. 4 are:

$$
t=\frac{-b \pm \sqrt{b^2 - 4ac}}{2a} \tag{6}
$$

If $$t<0$$ the ray crosses the sphere behind its origin. Note also that if $$\mathbf{B}$$ is a unitary vector, 
$$a = \mathbf{B} \cdot \mathbf{B} = 1$$.
