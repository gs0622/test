def fib(n):
    """ f(n) = f(n-1) + f(n-2), seed: f(0)=0, f(1)=1 """
    """ Print a Fibonacci series up to n """
    a,b = 0,1
    #print a
    while b<n:
        print b
        a,b = b,a+b
def main():
    fib(100)
if __name__ == '__main__':
    main()
    