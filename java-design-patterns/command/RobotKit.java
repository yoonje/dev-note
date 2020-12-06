import java.util.ArrayList;

public class RobotKit {
  private Robot robot = new Robot();
  private ArrayList<Command> commands = new ArrayList<Command>();

  public void addCommand (Command command) {
    commands.add(command);
  }
  public void start () {
    for (Command command : commands) {
      command.setRobot(robot);
      command.execute();
    }
  }
}