interface Thumbnail {
  public void showTitle ();
  public void showPreview ();
}

class RealThumbnail implements Thumbnail {
  private String title;
  private String movieUrl;

  public RealThumbnail (String _title, String _movieUrl) {
    title = _title;
    movieUrl = _movieUrl;

    // URL로부터 영상을 다운받는 작업 - 시간 소모 
    System.out.println(movieUrl + "로부터 " + title + "의 영상 데이터 다운");
  }
  public void showTitle () {
    System.out.println("제목:" + title);
  }
  public void showPreview () {
    System.out.println(title + "의 프리뷰 재생");
  }
}

class ProxyThumbnail implements Thumbnail {
  private String title;
  private String movieUrl;

  private RealThumbnail realThumbnail;

  public ProxyThumbnail (String _title, String _movieUrl) {
    title = _title;
    movieUrl = _movieUrl;
  }

  public void showTitle () {
    System.out.println("제목:" + title);
  }

  public void showPreview () {
    if (realThumbnail == null) {
      realThumbnail = new RealThumbnail(title, movieUrl);
    }
    realThumbnail.showPreview();
  }
}