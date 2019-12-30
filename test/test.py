
import subprocess

def test(expr, expected):

    proc = subprocess.Popen(["./evaluate", "-e", expr], stdout=subprocess.PIPE)
    output = proc.stdout.read()

    output = output.replace("\n", "")

    if output == expected:
        res = "OK"
    else:
        res = "FAILED"

    print "{}: Expression='{}'; expected={}; output={};".format(res, expr, expected, output)


if __name__ == "__main__":

    test("True", "true")
    test("1", "true")
    test("False", "false")
    test("0", "false")
    test("NOT True", "false")
    test("NOT False", "true")
    test("NOT 1", "false")
    test("NOT 0", "true")
    test("False OR False", "false")
    test("False OR True", "true")
    test("True OR False", "true")
    test("True OR True", "true")
    test("False AND False", "false")
    test("False AND True", "false")
    test("True AND False", "false")
    test("True AND True", "true")
    test("(True OR False) AND False", "false")
    test("(True OR False) AND 1 == True", "false")
    test("(True OR False) AND 1 == 1", "true")
    test("2 == 2", "true")
    test("2 eq 33", "false")
    test("-1 == 1", "false")
    test("-1 != 1", "true")
    test("-1 ne 1", "true")
    test("-1 < 0", "true")
    test("1 <= 10", "true")
    test("5 >= 1", "true")
    test("1 < 5 AND 5 < 10", "true")
    test("-1 in [-1, 0, 1]", "true")
    test("-1 in [0, 1, 2]", "false")
    test("\"This is a test\" sw \"This\"", "true")
    test("\"This is a test\" ew \"test\"", "true")
    test("\"This is a test\" contains \"is\"", "true")
    test("\"This is a test\" contains \"doh!\"", "false")
    test("\"This is a test\" contains True", "false")
    test("\"This is a test\" contains [30, 12, 2019]", "false")