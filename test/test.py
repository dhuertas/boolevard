#
# Boolean expression evaluator
# @author Dani Huertas
# @email huertas.dani@gmail.com
#
import subprocess

def test(expr, expected, params = None):

    cmd = ["./bxe"]

    if params != None and isinstance(params, list):
    
        cmd = cmd + params

    cmd = cmd + ["-e", expr]

    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    output = proc.stdout.read()

    output = output.replace("\n", "")

    if output == expected:
        res = "OK"
    else:
        res = "FAILED"

    if params != None:
        print "{}: Expression='{}'; Params='{}' expected={}; output={};".format(res, expr, params, expected, output)
    else:
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
    test("[1..2] == [1..2]", "true")
    test("[-2..3] == [2..3]", "false")
    test("-1 in [-2..3]", "true")
    test("[1..3] in [[1..1], [1..2], [1..3]]", "true")
    test("[-1..0] in [[1..1], [1..2], [1..3]]", "false")
    test("-1.0 eq -1", "true")
    test("2.001 > 2", "true")
    test("1.5 eq -1.5", "false")
    test("res < 2", "true", params = ["-a", "res=1"])
    test("res < 2", "true", params = ["-a", "res=1.5"])
    test("res < 2", "false", params = ["-a", "res=2.005"])
    test("str sw \"this is\"", "true", params = ["-a", "str=\"this is a test\""])
    test("str contains \" is a \"", "true", params = ["-a", "str=\"this is a test\""])
    test("str ew \" a test\"", "true", params = ["-a", "str=\"this is a test\""])
