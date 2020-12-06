interface Order {
  public void run (Robot robot);
}

class MoveBackOrder implements Order {
  private int block;

  public MoveBackOrder(int _block) {
    block = _block;
  }

  public void run (Robot robot) {
    robot.turn(Robot.Direction.LEFT);
    robot.turn(Robot.Direction.LEFT);
    robot.moveForward(block);
  }
}