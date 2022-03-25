Mainly focused on topics like linear models like linear regression / logistic regression and neural networks

## Gradient Descent

Gradient Descent requires **simultaneous** update - updating all parameters at the same time using the same learning rate instead of updating one parameter first, and then use updated parameter to calculate another parameter.

![](https://i.ibb.co/Lk6chns/image.png)

## Logistic regression model

logistic = feeding linear regression model $y = \beta \cdot x$ into sigmoid function

$$
p(x) = \frac{b^{\beta \cdot x}}{1+b^{\beta \cdot x}}= \frac{1}{1+b^{-\beta \cdot x}}=S_b(t)
$$

Cost functions for above model - It has been really hard for me to memorize the cost function for logistic regression. Hopefully, the picture below helps capture the intuition of how to design cost function.

![](https://i.ibb.co/2KxfZH0/image.png)

![](https://i.ibb.co/Dph2n3X/image.png)

$h_{\theta}x$ means hypothesis of model regarding relationships between $\theta$ and $x$

linear regression: $h_{\theta}x = \theta^Tx$

logistic regression: $h_{\theta}x = \frac{1}{1+e^{-\theta^Tx}}$

Another post explaining loss function in logistic regression:

[Loss Function (Part II): Logistic Regression | by Shuyu Luo | Towards Data Science](https://towardsdatascience.com/optimization-loss-function-under-the-hood-part-ii-d20a239cde11)

In multi-classification problem, one-vs-all provides a brute force way to solve the problem:

![](https://i.ibb.co/rKrjSj9/image.png)

Calculate manually in logistic regression

![](https://i.ibb.co/7g2BWtk/image.png)

## Regularization

Intuition in regularization: [Cost Function | Coursera](https://www.coursera.org/learn/machine-learning/supplement/1tJlY/cost-function)

> Note generally we don't know which $\theta$ to shrink i.e. which parameter OR parameters to shrink explicitly, but we want to remove the overall influence and penalize all parameters. That's why we use $\lambda \sum\limits_{j=1}^{n} \theta_{j}^2$ in which $\lambda$ capture the intuition of the extend of penalization.

![](https://i.ibb.co/pKrHrT0/image.png)

> The whole cost function consists of original cost function and an additional regularization term.
>
> So the larger $\lambda$ means the higher weight it has in the final cost function, meaning the regularization has higher amount of impact. Thus, in extreme case with very large regularization, the function can be underfitted.
>
> Likewise, the larger $C = 1/\lambda$ which is the parameter for original cost function (non regularization part) means less impact of the regularization. Thus, in extreme case with no regularization, the function is trying to do perfect job even it comes with overfitting.

[machine learning - What is the influence of C in SVMs with linear kernel? - Cross Validated (stackexchange.com)](https://stats.stackexchange.com/questions/31066/what-is-the-influence-of-c-in-svms-with-linear-kernel)

## Neural Networks

The main motivation behind neural network is that it can introduce non-linearity into the problems that can't be solved through linear models

[Examples and Intuitions I | Coursera](https://www.coursera.org/learn/machine-learning/supplement/kivO9/examples-and-intuitions-i)

![](https://i.ibb.co/yPSwczT/image.png)

![](https://i.ibb.co/NTWbFKX/image.png)

Backpropagation - The following post, I believe, gives a better explanation: [A Step by Step Backpropagation Example – Matt Mazur](https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/). The network usually starts with random initialization for all initial weights.

Backpropagation provides the "formal" way to compute gradient using chain rule i.e. you know exactly where to go upfront to optimize cost function. In contrast, gradient descent is like testing all directions to find the best direction.
