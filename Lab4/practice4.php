<?php
// practice4.php - generates a multiplication table based on POST input

$max = isset($_POST['multi_to_num']) && is_numeric($_POST['multi_to_num']) ? intval($_POST['multi_to_num']) : 10;

?><!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Practice 4</title>
</head>
<body>
    <h1>Practice 4: PHP Multiplication Table</h1>
    <form method="post" action="practice4.php">
        <label for="multi_to_num">Enter a number (default 10):</label>
        <input type="number" id="multi_to_num" name="multi_to_num" min="0">
        <input type="submit" value="Generate Multiplication Table">
    </form>
    <table border="1">
        <tr>
            <th>Multiplicand</th>
            <th>Multiplier</th>
            <th>Product</th>
        </tr>
    <?php
    for ($i = 1; $i <= $max; $i++) {
        for ($j = 1; $j <= $max; $j++) {
            echo "<tr>";
            echo "<td>$i</td>";
            echo "<td>$j</td>";
            echo "<td>" . ($i * $j) . "</td>";
            echo "</tr>";
        }
    }
    ?>
    </table>

</body>
</html>
