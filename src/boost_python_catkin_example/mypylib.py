"""Some simple example module that is going to be used in C++."""


def hello():
    """Return a hello message."""
    return "Hello C++. I'm Python, looking forward to work with you!"


class SomeClass:

    def __init__(self):
        self.value = None

    def set_value(self, value):
        self.value = value

    def get_value(self):
        return self.value
