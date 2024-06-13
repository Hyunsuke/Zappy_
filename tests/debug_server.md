For debug with telnet change '\n' by '\r\n' :
    run_commands_gui.c
     -> command = strtok(buffer, "\r\n");
    run_commands_ia.c
     -> command = strtok(buffer, "\r\n");
    handle_cmd.c
     -> team_name = strtok(buffer, "\r\n");
     -> if (strcmp(buffer, "GRAPHIC\r\n") == 0) {
