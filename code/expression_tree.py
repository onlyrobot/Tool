# definded a class: Expression
in_pri = { '=' : -1, '+' : 1, '-' : 1, '*' : 2, '/' : 2, '%' : 2, '^' : 4, '(' : 10 }
out_pri = { '=' : -1, '+' : 1, '-' : 1, '*' : 2, '/' : 2, '%' : 2, '^' : 3, '(' : 0 }
def error(error_message):
    print(error_message)
    exit()
def is_op(c):
    return True if ['=', '+', '-', '*', '/', '%', '^', '('].count(c) != 0 else False
class BiTreeNode:
    def __init__(self):
        self.body, self.left, self.right = None, None, None
    def __init__(self, body, right = None, left = None):
        self.body, self.left, self.right = body, left, right
class Expression:
    def __init__(self, str):
        # this.vars = dict()
        ns, os = list(), list()
        for c in str:
            if is_op(c):
                while os and in_pri[c] <= in_pri[os[-1]]:
                    try:
                        ns.append(BiTreeNode(os.pop(), ns.pop(), ns.pop()))
                    except:
                        error('error expression')
                os.append(c)
            elif c == ')':
                try:
                    op = os.pop()
                    while op != '(':
                        ns.append(BiTreeNode(op, ns.pop(), ns.pop()))
                        op = os.pop()
                except:
                    error('error expression')
            else:
                try:
                    c = float(c)
                except:
                    print('do nothing')
                ns.append(BiTreeNode(c))
        while os:
            try:
                ns.append(BiTreeNode(os.pop(), ns.pop(), ns.pop()))
            except:
                error('error expression')
        if len(ns) != 1:
            error('error expression')
        self.root = ns.pop()
    def calculate(self, root = None):
        if not root:
            root = self.root
        if root.left and root.right:
            funs = { '+' : lambda x, y : x + y, '-' : lambda x, y : x - y }
            return funs[root.body](self.calculate(root.left), self.calculate(root.right))
        else:
            if isinstance(root.body, str):
                return self.assignment[root.body]
            else:
                return root.body
    def print_expression(self, root = None, depth = 0):
        if not root:
            root = self.root
        if root.left:
            self.print_expression(root.left, depth + 1)
        print('    ' * (depth - 1), '' if depth == 0 else ' ---', end = '')
        print(root.body)
        if root.right:
            self.print_expression(root.right, depth + 1)
if __name__ == '__main__':
    eql = Expression(input('enter the expression:\n'))
    eql.print_expression()
    eql.assignment = { 'x' : 10 }
    print(eql.calculate())
