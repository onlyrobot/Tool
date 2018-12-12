import turtle
from datetime import *
def home():
    turtle.penup()
    turtle.home()
    turtle.pendown()
def jump(steps):
    turtle.penup()
    turtle.forward(steps)
    turtle.pendown()
def draw_clock_time():
    t = datetime.today()
    hour = t.hour
    minute = t.minute
    second = t.second
    angle_of_hour = hour / 12 * 360 + minute / 60 * 30
    angle_of_minute = minute / 60 * 360 + second / 60 * 6
    angle_of_second = second / 60 * 360
    #覆盖之前画的
    home()
    turtle.pencolor("white")
    turtle.dot(180)
    turtle.pencolor("black")
    #画中心点
    home()
    turtle.dot(12)
    #画时针
    home()
    turtle.right(angle_of_hour)
    turtle.pensize(4)
    turtle.forward(40)
    #画分针
    home()
    turtle.right(angle_of_minute)
    turtle.pensize(3)
    turtle.forward(60)
    #画秒针
    home()
    turtle.right(angle_of_second)
    turtle.pensize(2)
    turtle.forward(80)
    #循环
    turtle.ontimer(draw_clock_time, 100);
def init():
    angle = 0
    #画刻度线和数字
    for i in range(60):
        home()
        turtle.right(angle)
        angle += 6
        jump(100)
        if i % 5 == 0:
            turtle.pensize(5)
            turtle.forward(10)
            turtle.penup();
            if i <= 20 or i >= 40:
                turtle.forward(3)
            else:
                turtle.forward(20)
            if i == 0:
                turtle.write(12, align = 'center', font = ("Courier", 14, "bold"))
            else:
                turtle.write(int(i // 5), align = 'center', font = ("Courier", 14, "bold"))
        else:
            turtle.pensize(3)
            turtle.dot(3)
def main():
    turtle.mode("logo")
    turtle.tracer(False)
    turtle.hideturtle()
    init()
    draw_clock_time()
    turtle.done()
if __name__ == '__main__':
    main()