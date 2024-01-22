# import turtle
#
# # Functie om de L-systeemregels toe te passen
# def apply_rules(symbol, stack):
#     if symbol == 'F':
#         turtle.forward(10)
#     elif symbol == '+':
#         turtle.left(25)
#     elif symbol == '-':
#         turtle.right(25)
#     elif symbol == '[':
#         state = turtle.position()
#         angle = turtle.heading()
#         stack.append((state, angle))
#     elif symbol == ']':
#         state, angle = stack.pop()
#         turtle.penup()
#         turtle.goto(state)
#         turtle.setheading(angle)
#         turtle.pendown()
#
# # Functie om het L-systeem te interpreteren
# def interpret_lsystem(lsystem_output):
#     stack = []
#     for symbol in lsystem_output:
#         apply_rules(symbol, stack)
#
# # Hoofdfunctie
# def main():
#     turtle.speed(0)  # Snelheid van de turtle
#
#     # # Hier wordt het tekstbestand geopend en de inhoud gelezen
#     # with open("C:\\Clion\\LSystem_Interpreter\\sources\\turtle.txt", "r") as file:
#     #     lsystem_output = file.read()
#     #
#     # interpret_lsystem(lsystem_output)
#     # turtle.exitonclick()
#
#     with open("C:\\Clion\\LSystem_Interpreter\\sources\\beautiful_tree.txt", "r") as file:
#         lsystem_output2 = file.read()
#
#     interpret_lsystem(lsystem_output2)
#     turtle.exitonclick()
#
# if __name__ == "__main__":
#     main()

import turtle
from turtle import Turtle


def drawfile(name, distance, angle):

    t = Turtle()
    t.screen.title('LSystemTurtle')
    #t.screen.bgcolor("green")
    t.color("green")

    t.speed("fastest")
    t.up()
    t.goto(0, 0)
    t.down()
    t.seth(90)


    with open(name, "r") as file:
     output = file.read()

    stack = []

    for symbol in output:
        if symbol == 'F':
            turtle.forward(distance)
        elif symbol == '+':
            turtle.left(angle)
        elif symbol == '-':
            turtle.right(angle)
        elif symbol == '[':
        #push location on stack = save position and heading
            stack.append((t.position(), t.heading()))
        elif symbol == ']':
        #pop location on stack
            position, heading = stack.pop()
            t.up()
            t.goto(position)
            t.seth(heading)
            t.down()
    turtle.exitonclick()

#drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\turtle.txt",2 ,30)
#!!drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\beautiful_tree.txt",2 ,30)
#drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\new_tree.txt", 2, 23)
#drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\tree2.txt",2 , 23)
#!drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\beautiful_tree2.txt",2 ,30)
drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\beautiful_tree3.txt",2 ,30)
#drawfile("C:\\Clion\\LSystem_Interpreter\\sources\\turtleeee_output.txt",2 ,30)