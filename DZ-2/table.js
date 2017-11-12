$(document).ready(function() {
    row_number = 20
    column_number = 26
    columns = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
    cell_expressions = {}

    function GetLength(a) { 
        return a.length; 
    }

    function EvalExpression(expression, cell_id) {
        if (expression[0] == "=") {
            expression = expression.slice(1);
            expression = expression.split("ABS").join("Math.abs");
            expression = expression.split("SIN").join("Math.sin");
            expression = expression.split("LEN").join("GetLength");
            
            for(var i = 0; i < column_number; i++) {
                for (j = row_number; j >= 0; j--) {
                    var cell_idToBeFound = columns[i] + j.toString();
                    if (expression.indexOf(cell_idToBeFound) !== -1) {
                        var val = EvalExpression(cell_expressions[cell_idToBeFound]);
                        expression = expression.split(cell_idToBeFound).join(val.toString());
                    }
                }
            }
            try {
                var lenSplitParts = expression.split("GetLength(");
                for (var i = 1; i < lenSplitParts.length; i++) {
                    if (lenSplitParts[i][0] != "\"" && lenSplitParts[i][0] != "'") {
                        var bracketSplit = lenSplitParts[i].split(")");
                        bracketSplit[0] = '"' + bracketSplit[0] + '"';
                        lenSplitParts[i] = bracketSplit.join(")");
                    }
                }
                expression = lenSplitParts.join("GetLength(");
                expression = eval(expression);
            } catch(e) {                
                expression = "";
                console.log("Error 1")
                throw "Error 1"
            }
        }
        return expression;
    }

    for(var i = 0; i < column_number; i++){
        for (j = 1; j <= row_number; j++) {
            var cell_id = columns[i] + j.toString();
            cell_expressions[cell_id] = "";
            $('#' + cell_id).val("");
            $('#' + cell_id).focusin(function() { 
                                    $(this).val(cell_expressions[$(this).attr('id')]); 
                                });
            $('#' + cell_id).focusout(function() { 
                                    cell_expressions[$(this).attr('id')] = $(this).val();
                                    var evalRes = "";
                                    try {
                                        evalRes = EvalExpression($(this).val(), $(this).attr('id'));
                                    } catch(e) {
                                    }
                                    $(this).val(evalRes); 
                                });
        }
    } 
});