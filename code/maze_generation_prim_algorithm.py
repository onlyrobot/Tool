# maze generate with prim algorithm
import random
import turtle
VISITED = 1
PATH = 1
ROW, COL = 30, 30
DIRS = [(-1, 0), (0, 1), (1, 0), (0, -1)]
maze = [[[0, 0, 0, 0, 0] for i in range(COL)] for i in range(ROW)]
START, END = (0, 0), (ROW - 1, COL - 1)
que = [START]
def cross_border(cell):
    return cell[0] < 0 or cell[0] >= ROW or cell[1] < 0 or cell[1] >= COL
def visited(cell):
    return maze[cell[0]][cell[1]][4] == 1
def fill_rectangle(x, y, width, height):
    turtle.penup()
    turtle.goto(x, y)
    # turtle.pendown()
    turtle.begin_fill()
    turtle.forward(width)
    turtle.right(90)
    turtle.forward(height)
    turtle.right(90)
    turtle.forward(width)
    turtle.right(90)
    turtle.forward(height)
    turtle.right(90)
    turtle.end_fill()
def draw_maze():
    CELL_SIZE = 10
    BORDER_SIZE = 2
    turtle.setup(ROW * CELL_SIZE, COL * CELL_SIZE)
    turtle.hideturtle()
    turtle.speed(0)
    turtle.pensize(0)
    for i in range(ROW):
        for j in range(COL):
            x = -ROW * CELL_SIZE / 2 + j * CELL_SIZE
            y = COL * CELL_SIZE / 2 - i * CELL_SIZE
            width, height = CELL_SIZE, CELL_SIZE
            if maze[i][j][0] != PATH:
                fill_rectangle(x - BORDER_SIZE, y, CELL_SIZE + 2 * BORDER_SIZE, BORDER_SIZE)
            if maze[i][j][1] != PATH:
                fill_rectangle(x + CELL_SIZE - BORDER_SIZE, y + BORDER_SIZE, BORDER_SIZE, CELL_SIZE + 2 * BORDER_SIZE)
            if maze[i][j][2] != PATH:
                fill_rectangle(x - BORDER_SIZE, y - CELL_SIZE + BORDER_SIZE, CELL_SIZE + 2 * BORDER_SIZE, BORDER_SIZE)
            if maze[i][j][3] != PATH:
                fill_rectangle(x, y + BORDER_SIZE, BORDER_SIZE, CELL_SIZE + 2 * BORDER_SIZE)
    turtle.done()
    return 0
def print_maze():
    return 0
if __name__ == '__main__':
    while que:
        r, c = que.pop(random.randint(0, len(que) - 1))
        maze[r][c][4] = VISITED
        dirs = []
        for dir in DIRS: # four direction
            cell = (r + dir[0], c + dir[1])
            if not cross_border(cell):
                if visited(cell):
                    dirs.append(dir)
                elif maze[cell[0]][cell[1]][4] == 0:
                    que.append(cell)
                    maze[cell[0]][cell[1]][4] = 2
        if dirs:
            dir = random.choice(dirs)
            index = DIRS.index(dir)
            maze[r][c][index] = PATH
            maze[r + dir[0]][c + dir[1]][index + 2 if index < 2 else index - 2] = PATH
    maze[START[0]][START[1]][3] = 1 # entrance
    maze[END[0]][END[1]][2] = 1 # exit
    draw_maze()
