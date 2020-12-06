abstract class Component {
  protected abstract String getCompName ();
  public Component () {
    System.out.println(this.getCompName() + " 생성");
  }
}

class Button extends Component {
  @Override
  protected String getCompName() { return "버튼"; }
}
class Switch extends Component {
  @Override
  protected String getCompName() { return "스위치"; }
}
class Dropdown extends Component {
  @Override
  protected String getCompName() { return "드랍다운"; }
}