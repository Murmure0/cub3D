#!/bin/bash

echo --- MAP ERROR TESTER ---
echo 1. maps/Not_valid/empty_file.cub
./cub3d maps/Not_valid/empty_file.cub
echo ---
echo 2. maps/Not_valid/empty_line_in_map.cub
./cub3d maps/Not_valid/empty_line_in_map.cub
echo ---
echo 3. maps/Not_valid/excess_params.cub
./cub3d maps/Not_valid/excess_params.cub
echo ---
echo 4. maps/Not_valid/excess_player.cub
./cub3d maps/Not_valid/excess_player.cub
echo ---
echo 5. maps/Not_valid/forbidden_char.cub
./cub3d maps/Not_valid/forbidden_char.cub
echo ---
echo 6. maps/Not_valid/map_too_small.cub
./cub3d maps/Not_valid/map_too_small.cub
echo ---
echo 7. maps/Not_valid/missing_param.cub
./cub3d maps/Not_valid/missing_param.cub
echo ---
echo 8. maps/Not_valid/missing_player.cub
./cub3d maps/Not_valid/missing_player.cub
echo ---
echo 9. maps/Not_valid/random_line.cub
./cub3d maps/Not_valid/random_line.cub
echo ---
echo 10. maps/Not_valid/wrong_extension.ber
./cub3d maps/Not_valid/wrong_extension.ber
echo ---
# echo 11 maps/Not_valid/wrong_texture.cub //Kinda broken
# ./cub3d maps/Not_valid/wrong_texture.cub
# echo ---
echo 	-- WALL TESTS --
echo 12. maps/Not_valid/1st_line.cub
./cub3d maps/Not_valid/1st_line.cub
echo ---
echo 13. maps/Not_valid/last_line.cub
./cub3d maps/Not_valid/last_line.cub
echo ---
echo 14. maps/Not_valid/left_wall.cub
./cub3d maps/Not_valid/left_wall.cub
echo ---
echo 15. maps/Not_valid/right_wall.cub
./cub3d maps/Not_valid/right_wall.cub
echo ---
