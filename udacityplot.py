import matplotlib, matplotlib.pyplot
import numpy
import types

def show_plot(arg1, arg2=None):

    def real_decorator(f):
        def wrapper(*args, **kwargs):
            matplotlib.pyplot.figure(figsize=(arg1, arg2))
            result = f(*args, **kwargs)
            matplotlib.pyplot.show()
            return result
        return wrapper

    if type(arg1) == types.FunctionType:
        f = arg1
        arg1, arg2 = 10, 5
        return real_decorator(f)
    return real_decorator

# SIMPLE
# Plots square root function from 0 to 100
import math
#from udacityplots import *

@show_plot
def simple():
    x_data = numpy.linspace(0., 100., 1000)

    for x in x_data:
        y = math.sqrt(x)
        matplotlib.pyplot.scatter(x, y)

    axes = matplotlib.pyplot.gca()
    axes.set_xlabel('x')
    axes.set_ylabel('y')

simple()

if __name__ == '__main__':
	main()
