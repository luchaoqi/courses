## Metrics in Machine Learning System Design

Bias and variance: [Diagnosing Bias vs. Variance | Coursera](https://www.coursera.org/learn/machine-learning/supplement/81vp0/diagnosing-bias-vs-variance)

$J_{CV}$ denotes cross validation error which is the same as validation error $J_V$

![](https://i.ibb.co/fVJFrQ2/image.png)

![](https://i.ibb.co/c3bg9n9/image.png)

Precision vs. Recall

Note that, in convention, $y=1$ usually presents **rare** class OR class we are **more** interested in e.g. patients with cancer we want to detect

![](https://i.ibb.co/YyWYH3M/image.png)

PR curve

Note the PR curve gives precision and recall at all thresholds - high threshold gives high precision but low recall, low threshold gives low precision but high recall (this is what we want in the cancer example)

![](https://i.ibb.co/bb7NnbZ/image.png)

How to choose a good threshold?

A: use F-score, $F_1 Score = 2\frac{PR}{P+R}$, in mathematics, this is called the harmonic mean of precision and sensitivity.

## SVM

The intuition of designing loss function for logistic regression should gives some clue how we design it in SVM:

![](https://i.ibb.co/SQnHKLR/image.png)

![](https://i.ibb.co/CbVKd3Z/image.png)

![](https://i.ibb.co/zRwbRjv/image.png)

I think I mentioned it previously:

> The whole cost function consists of original cost function and an additional regularization term.
>
> So the larger $\lambda$ means the higher weight it has in the final cost function, meaning the regularization has higher amount of impact. Thus, in extreme case with very large regularization, the function can be underfitted.
>
> Likewise, the larger $C = 1/\lambda$ which is the parameter for original cost function (non regularization part) means less impact of the regularization. Thus, in extreme case with no regularization, the function is trying to do perfect job even it comes with overfitting.

[machine learning - What is the influence of C in SVMs with linear kernel? - Cross Validated (stackexchange.com)](https://stats.stackexchange.com/questions/31066/what-is-the-influence-of-c-in-svms-with-linear-kernel)

So here, Andrew is trying to illustrate the case that SVM is trying to separate two classes without any errors:

![](https://i.ibb.co/BGYyF3g/image.png)

[Udacity](https://www.youtube.com/watch?v=5yzSv4jYMyI&list=PLgIPpm6tJZoShjm7r8Npia7CMsMlRWeuZ&index=1) provides another understanding of the optimization problem.

For two vectors $x_{1},x_{2}$ that are on two support vectors we have:

$$
\begin{array}{l}{\omega^{\top} x_{1}+b=1} \\ {\omega^{\top} x_{2}+b=-1}\end{array}
$$

If you subtract them, the distance between planes (i.e. margin) can be presented as

$$
\frac{\omega^{T}\left(x_{1}-x_{2}\right)}{\|\omega\|}=\frac{2}{\|\omega\|}
$$

s.t. for two classifications/labels $y_i = 1/-1$, $y_i*(w^Tx_i+b) \geq 1$

**Why? Because $w^T$ is the direction vertical to the hyperplane so the left part means exactly the projected distance of the vector $x_{1} - x_{2}$  on unit vector $w^T / \|w^T\|$**

![](https://www.researchgate.net/publication/304611323/figure/fig8/AS:668377215406089@1536364954428/Classification-of-data-by-support-vector-machine-SVM.png)

> Why $w^T$ is vertical to the hyperplane?
>
> Imagine two points on the hyperplane $w^Tx+b =0$
>
> $w^Tx_1+b = w^Tx_2+b = 0$
>
> $w^T(x_1-x_2)=0$
>
> $x_{1} - x_{2}$ is the vector on the hyperplane and thus $w ^T$ is the normal vector. bam!!!

Maximizing the margin equals to minimizing the reciprocal along with monotone

$$
\begin{array}{l}{\max \frac{2}{\| w \|}} \\ {\min 1 / 2\|w\|^{2}}\end{array}
$$

### Polynomial Kernel

I personally prefer explanations from Josh here: [Video Index - StatQuest!!!](https://statquest.org/video-index/) (there are three videos)

[Support Vector Machines Part 2: The Polynomial Kernel (Part 2 of 3) - YouTube](https://www.youtube.com/watch?v=Toet3EiSFcM)

Polynomial kernel formula:

$$
(a * b + r)^d \\
a.b: \text{a and b refer to two different data in the dataset (1 dimension)} \\
r: \text{r determines the coefficient of polynomial} \\
d: \text{d determines the degree of polynomial}
$$

Note $r$ and $d$ are determined through cross validation, here we set $r = 1$ and $d = 2$ for illustration

$$
(a*b+1)^2 = (\sqrt{2}a,a^2,1)\cdot(\sqrt{2}b,b^2,1)
$$

**It means we create two new features (constant 1 is the same so we ignore it): $\sqrt{2}*x, x^2$ to help differentiate original $a$ and $b$ where there is only one feature $x$**

**In practice, we can directly plug values into the kernel where the output represents the relationship between two data in 2-dimensions without actually transform the data to 2-Dimensions.**

### Radial Kernel

[Support Vector Machines Part 3: The Radial (RBF) Kernel (Part 3 of 3) - YouTube](https://www.youtube.com/watch?v=Qc5IyLW_hns)

RBF formula:

$$
e^{-\gamma(a - b)^2} \\
\gamma: \text{determines the scale of influence two points have on each other}
$$

Go through the video and you will find `<mark>` how RBF kernel defines the relationship between two points in infinite-dimensions is genius!`</mark>`

Let's set $\gamma=1/2$ for illustration:

$e^{-1/2(a - b)^2} = e^{-1/2(a^2+b^2)} e^{ab}$

With Taylor Series Expansion: $e^x = f(a)+\frac {f'(a)}{1!} (x-a)+ \frac{f''(a)}{2!} (x-a)^2+\frac{f'''(a)}{3!}(x-a)^3+ \cdots$

We set $a = 0$ for series above and replace x with ab

![](https://i.ibb.co/6r86Jvh/image.png)
![](https://i.ibb.co/bjhpMDH/image.png)

**So, for original coordinates that has only one dimension $x$, the new coordinates are of infinite number of dimensions.**

**Note, like mentioned before, we are not actually projecting data into infinite number of dimensions and then try to figure out how to separate them in SVM. Instead, we plug the value into kernel function where the output (a single number) represents the relationship between two data points.**

## K-Means

```python
from statistics import mean

def cal_dist(p1,p2):
    return sum((a-b)**2 for a,b in zip(p1,p2))**0.5

def kmeans(dataset,k,threshold=1e-10,n_iter=50):
    """
    Args:
        dataset : array
        k : number of K
        threshold : centroids merge threshold e.g. dist(prev_centroid,new_centroid) <= thrshold == same_centroid
        n_iter : maximum number of iterations
    Returns:
        location of final centroids
    """
    dataset = [tuple(i) for i in dataset]
    prev_centroids = {i: [] for i in dataset[:k]}
    for n in range(1, n_iter + 1):
        for data in dataset: # step1: assign datapoint to its closest centroid
            closest_centroid = min(prev_centroids,key=lambda x:cal_dist(data,x))
            prev_centroids[closest_centroid].append(data)

        cur_centroids = []
        for centroid, cluster in prev_centroids.items(): # calculate new centroid
            mean_x,mean_y = mean(c[0] for c in cluster),mean(c[1] for c in cluster)
            cur_centroids.append((mean_x,mean_y))

        # return if all new centroids are close (dist <= threshold) to old centroids
        if all(cal_dist(p,q) <= threshold for p,q in zip(prev_centroids.keys(),cur_centroids)):
            print(f'Optimization finished with {n} iterations')
            for k,v in prev_centroids.items():
                print(k,':',v)
            break

        # update prev_centroids with cur_centroids
        prev_centroids = {centroid:[] for centroid in cur_centroids}

    return cur_centroids
# A = [(random.randint(0,10),random.randint(0,10)) for _ in range(1000)]
A = [[1,1],[2,1],[4,3],[5,4],[100,10],[20,20]]
print(kmeans(A,2))

```

### Elbow Method

When trying to determine number of K in K-Means, we can use "elbow" method.

![](https://i.ibb.co/RHXhTsK/image.png)

Similarly in PCA, when trying to determine the number of principal component for further analysis, we can use this method in scree plot.

From my previous manuscript:

> However, inferentially determining the number of PCs remains a difficult task and there is no single approach. To address this problem, 10-fold cross-validation was used. The first 50 PCs were used in cross-validation while always keeping other covariates. The overall root-mean-square error (RMSE) and R-squared would be our metrics when evaluating model performance. Note that the smallest RMSE or the largest R-squared doesn’t significantly indicate the best number of PCs to use in the model. Overfitting may occur and affect the predictive accuracy of the regression model with a new dataset. As such, a nested model search was performed using F-tests on groupings of variables. Thus, we compared nested models without any principal components of daily activity and models with different numbers of components.

[GraphPad Prism 9 Curve Fitting Guide - How the F test works to compare models](https://www.graphpad.com/guides/prism/latest/curve-fitting/reg_howtheftestworks.htm)

## PCA

The mathematics to inferentially understand why `calculating eigen decomposition of covariance matrix` == `getting the principal component that minimize the distance to PC/maximize the variance of projections` is included in my github repo.

### eigen-decomposition of covariance matrix

```python
import numpy as np

def pca(data):
    # scale data based on mean of features
    feature_mean = np.mean(data.T,axis=1)
    data_std = data - feature_mean

    covMatrix = np.cov(data_std.T)
    eigenValues, eigenVectors = np.linalg.eig(covMatrix)
    # eigenVectors: The normalized (unit “length”) eigenvectors, such that the column v[:,i] is the eigenvector corresponding to the eigenvalue w[i].
    idx = eigenValues.argsort()[::-1]
    eigenValues = eigenValues[idx]
    eigenVectors = eigenVectors[:,idx]

    projections = data_std @ eigenVectors # definitions of dot product of two vectors/matrices

    print(eigenValues)
    print(eigenVectors)
    print(projections)
    # projections[0] is the projection of data_std[0] in the new coordinates

x = [-1,-1,0,2,0]
y = [-2,0,0,1,1]
data = np.array([[i,j] for i,j in zip(x,y)])
pca(data)

# [2.5 0.5]
# [[ 0.70710678 -0.70710678]
#  [ 0.70710678  0.70710678]]
# [[-2.12132034 -0.70710678]
#  [-0.70710678  0.70710678]
#  [ 0.          0.        ]
#  [ 2.12132034 -0.70710678]
#  [ 0.70710678  0.70710678]]
```

### SVD

The SVD decomposition is heavily linear algebra required, please read through some main concepts here:

[Symmetric matrix - Wikipedia](https://en.wikipedia.org/wiki/Symmetric_matrix#Decomposition)

[Eigendecomposition of a matrix - Wikipedia](https://en.wikipedia.org/wiki/Eigendecomposition_of_a_matrix#Eigendecomposition_of_a_matrix)

[dimensionality reduction - Relationship between SVD and PCA. How to use SVD to perform PCA? - Cross Validated (stackexchange.com)](https://stats.stackexchange.com/questions/134282/relationship-between-svd-and-pca-how-to-use-svd-to-perform-pca)

[linear algebra - Why does Andrew Ng prefer to use SVD and not EIG of covariance matrix to do PCA? - Cross Validated (stackexchange.com)](https://stats.stackexchange.com/questions/314046/why-does-andrew-ng-prefer-to-use-svd-and-not-eig-of-covariance-matrix-to-do-pca)

> The singular value decomposition of a matrix $A$ is $A=U\Sigma V^T$, where the columns of $V$ are eigenvectors of $A^TA$ and the diagonal entries of $\Sigma$ are the **square roots** of its eigenvalues, i.e. $\sigma_{ii}=\sqrt{\lambda_i(A^TA)}$.
>
> Multiplying a matrix by a scalar leaves the eigenvectors unchanged and multiplies every eigenvalue by the same scalar.

$\mathbf{C} \text{(covariance matrix)}=\mathbf{X}^{\top} \mathbf{X} /(n-1)$

Wikipadia on symmetric matrix: Diagonalizable symmetric covariance matrix C can be decomposed as

$\mathbf{C}=\mathbf{V} \mathbf{L} \mathbf{V}^{\top} (1)$

If we now perform singular value decomposition of X, we obtain a decomposition

$\mathbf{X}=\mathbf{U S} \mathbf{V}^{\top}$

$\mathbf{C}=\mathbf{V S} \mathbf{U}^{\top} \mathbf{U S V}^{\top} /(n-1)=\mathbf{V} \frac{\mathbf{S}^{2}}{n-1} \mathbf{V}^{\top} (2)$

Compare `equation 1` vs. `equation 2`, they are the same. So there are 2 ways to get eigenvectors of covariance matrix

1. `equation 1` SVD of covariance matrix to get eigenvectors of covariance matrix $C$
2. `equation 2` SVD of raw matrix $X$ is the same as SVD of covariance matrix $C$ ($L = S_{raw}^2/(n-1)$)

```python
def pca(data):
    data = data.T
    m,n = data.shape
    data_trans = 1/np.sqrt(n-1) * data.T
    u, s, vh = np.linalg.svd(data_trans)
    print(s**2/np.sum(s**2)) # explained_variance_ratio_
    print(vh)
    print(data.T @ vh)

pca(data)

# [0.83333333 0.16666667]
# [[ 0.70710678  0.70710678]
#  [ 0.70710678 -0.70710678]]
# [[-2.12132034  0.70710678]
#  [-0.70710678 -0.70710678]
#  [ 0.          0.        ]
#  [ 2.12132034  0.70710678]
#  [ 0.70710678 -0.70710678]]
```

### [The art of using t-SNE for single-cell transcriptomics | Nature Communications](https://www.nature.com/articles/s41467-019-13056-x)

[t-SNE Initialization Options (jlmelville.github.io)](https://jlmelville.github.io/smallvis/init.html)

[Initialization is critical for preserving global data structure in both t-SNE and UMAP | Nature Biotechnology](https://www.nature.com/articles/s41587-020-00809-z)

[dkobak/tsne-umap-init: Initialization is critical for preserving global data structure in both t-SNE and UMAP (github.com)](https://github.com/dkobak/tsne-umap-init)

```python
# What happens if we do standardization before PCA
import numpy as np
# preprocessing
librarySizes = np.array(np.sum(batch003['counts'], axis=1))
# librarySizes = np.sum(batch003['counts'], axis=1).reshape(-1, 1)
X = np.log2(batch003['counts'][:, importantGenes_idx] / librarySizes * np.median(librarySizes) + 1)
X = np.array(X)
X = X - X.mean(axis=0)
X = X / X.std(axis=0)
# pca to speed up algorithm
U,s,V = np.linalg.svd(X, full_matrices=False)
U[:, np.sum(V,axis=1)<0] *= -1
X = np.dot(U, np.diag(s))
X = X[:, np.argsort(s)[::-1]][:,:50]
X = X / np.max(np.abs(X))
# pca-based tsne
PCAinit = X[:,:2] / np.std(X[:,0]) * .0001
Z = fast_tsne(X, perplexity=30, initialization=PCAinit)
```

### Don't abuse PCA

The problem of PCA is that it only works well when the first 2 principal components account for most of the variation in the data

[UMAP Dimension Reduction, Main Ideas!!! - YouTube](https://www.youtube.com/watch?v=eN0wFzBA4Sc)

It's a bad idea to use PCA to prevent overfitting - use PCA wisely

![](https://i.ibb.co/KXLXvMQ/image.png)

Don't abuse it and use it only when raw data (original features) doesn't work

![](https://i.ibb.co/s9mGjdq/image.png)

When to use PCA:

![](https://i.ibb.co/q9nt45S/image.png)
