import matplotlib.pyplot as plt

def lt(a, b):
    for i in range(len(a)):
        if a[i] < b[i]:
            return False
    return True

def minimalElements(A):
    minimal_elements = []
    for a in A:
        found = False

        for m in minimal_elements:
            if lt(m, a):
                minimal_elements.remove(m)
            elif lt(a, m):
                found = True
                break

        if not found:
            minimal_elements.append(a)
    
    return minimal_elements

def draw(all_elements, minimal_elements):
    plt.figure(figsize=(4, 4))

    for a in all_elements:
        plt.scatter(a[0], a[1], color='blue')

    for m in minimal_elements:
        plt.scatter(m[0], m[1], color='red')

    plt.show()

grid1 = [(n, k) for n in range(0, 10) for k in range(0, 10) if n * k >= 11]
print("Minimals elements of set A = { (n, k) | n, k ∈ [0, 100) and n * k >= 11 } are:")
print(minimalElements(grid1))
draw(grid1, minimalElements(grid1))

grid2 = [(n, k) for n in range(0, 100) for k in range(0, 100) if (n - 10)**2 + (k - 10)**2 <= 25]
print("Minimals elements of set B = { (n, k) | n, k ∈ [0, 100) and (n - 10)^2 + (k - 10)^2 <= 25 } are:")
print(minimalElements(grid2))
draw(grid2, minimalElements(grid2))
