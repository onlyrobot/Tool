# maze generate
import random
import operator
import turtle
PATH = 0
WALL = 1
UNCLEAR = 2
ROW, COL = 50, 50
START, END = (0, 0), (ROW - 1, COL - 1)
maze = [[UNCLEAR for i in range(COL)] for i in range(ROW)]
def path_count(cell):
    count = 0
    if cell[0] > 0 and maze[cell[0] - 1][cell[1]] == PATH:
        count += 1
    if cell[1] < COL - 1 and maze[cell[0]][cell[1] + 1] == PATH:
        count += 1
    if cell[0] < ROW - 1 and maze[cell[0] + 1][cell[1]] == PATH:
        count += 1
    if cell[1] > 0 and maze[cell[0]][cell[1] - 1] == PATH:
        count += 1
    return count
def find_path(cell):
    if operator.eq(cell, END):
        return True
    if cell[0] > 0 and maze[cell[0] - 1][cell[1]] == PATH:
        maze[cell[0] - 1][cell[1]] = 6
        if find_path((cell[0] - 1, cell[1])):
            return True
        maze[cell[0] - 1][cell[1]] = PATH
    if cell[1] < COL - 1 and maze[cell[0]][cell[1] + 1] == PATH:
        maze[cell[0]][cell[1] + 1] = 6
        if find_path((cell[0], cell[1] + 1)):
            return True
        maze[cell[0]][cell[1] + 1] = PATH
    if cell[0] < ROW - 1 and maze[cell[0] + 1][cell[1]] == PATH:
        maze[cell[0] + 1][cell[1]] = 6
        if find_path((cell[0] + 1, cell[1])):
            return True
        maze[cell[0] + 1][cell[1]] = PATH
    if cell[1] > 0 and maze[cell[0]][cell[1] - 1] == PATH:
        maze[cell[0]][cell[1] - 1] = 6
        if find_path((cell[0], cell[1] - 1)):
            return True
        maze[cell[0]][cell[1] - 1] = PATH
    return False
def print_maze():
    for i in maze:
        for j in i:
            print(j, end = '')
        print()
def draw_maze():
    CELL_SIZE = 10
    turtle.hideturtle()
    turtle.speed(0)
    turtle.setup(ROW * CELL_SIZE, COL * CELL_SIZE)
    turtle.pensize(3)
    turtle.penup()
    turtle.goto(-ROW * CELL_SIZE / 2, COL * CELL_SIZE / 2)
    turtle.pendown()
    turtle.forward(COL * CELL_SIZE)
    turtle.right(90)
    turtle.forward(ROW * CELL_SIZE)
    turtle.right(90)
    turtle.forward(COL * CELL_SIZE)
    turtle.right(90)
    turtle.forward(ROW * CELL_SIZE)
    turtle.right(90)
    turtle.pensize(0)
    turtle.write('S')
    for i in range(ROW):
        for j in range(COL):
            if maze[i][j] == WALL or maze[i][j] == UNCLEAR:
                turtle.penup()
                turtle.goto(-ROW * CELL_SIZE / 2 + j * CELL_SIZE, COL * CELL_SIZE / 2 - i * CELL_SIZE)
                turtle.pendown()
                turtle.begin_fill()
                for k in range(4):
                    turtle.forward(CELL_SIZE)
                    turtle.right(90)
                turtle.end_fill()
    turtle.penup()
    turtle.goto((ROW + 1) * CELL_SIZE / 2, -ROW * CELL_SIZE / 2 - CELL_SIZE)
    turtle.write('E')
    turtle.done()
if __name__ == '__main__':
    que = [START]
    while que: # start to generate maze
        pos = random.randint(0, len(que) - 1)
        cell = que.pop(pos)
        if path_count(cell) < 2:
            maze[cell[0]][cell[1]] = 0 # make it a path
            if cell[0] > 0 and maze[cell[0] - 1][cell[1]] == UNCLEAR:
                que.append((cell[0] - 1, cell[1]))
            if cell[1] < COL - 1 and maze[cell[0]][cell[1] + 1] == UNCLEAR:
                que.append((cell[0], cell[1] + 1))
            if cell[0] < ROW - 1 and maze[cell[0] + 1][cell[1]] == UNCLEAR:
                que.append((cell[0] + 1, cell[1]))
            if cell[1] > 0 and maze[cell[0]][cell[1] - 1] == UNCLEAR:
                que.append((cell[0], cell[1] - 1))
        else:
            maze[cell[0]][cell[1]] = WALL # make it a wall
    # find_path(START) # solve the maze, mark the path as 6
    # print_maze()
    draw_maze()
