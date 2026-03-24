[개발 개요]
- MFC의 CColorDialog 대신 사용할 색상 선택창 개발
- CDialog를 동적 생성 (리소스 사용안함)
- 버튼과 콤보로 표시?
- 클릭 시 팔레트 표시?
	- 처음 클릭 시 기본 팔레트를 표시하고 다른 색을 누르면 벌집팔레트, 사용자 지정을 누르면 ARGB, HSL 입력?
- 스포이트를 누르면 전체 모니터 캡처 및 표시하고 임의의 픽셀 클릭 시 색상 선택됨
- 최근 선택했던 색상들을 기억하고 레지스트리에 저장하여 다음 실행 시에도 사용할 수 있도록 함
- 사용자 정의색을 표시하는 영역이 필요하고 추가까지 할 수 있는 기능 필요(Goggle Slides의 색상선택박스와 동일)

[사용 방법]
- CSCColorPicker picker;
  picker.DoModal();	//가장 최근 선택했던 색이 선택된 상태로 실행
  picker.DoModal(_T("Color Picker"), Gdiplus::Color(255, 255, 0, 191)); //제목과 색상을 지정하여 실행
  picker.get_color();

[수정할 내용]
- 클립보드로 복사 버튼 추가

[수정된 내용]
- recent color는 총 8개를 표시할 수 있지만 정보를 지우진 않는다. 마우스 휠 또는 드래그로 스크롤되도록 한다.
- 슬라이더 맨 오른쪽 1px 잘림
- 반투명 회색일 경우 선택 표시가 흰색이라 잘 구분되지 않음
- hsv edit 추가
- 팝업메뉴 표시(툴팁, 최근 색상 내보내기, 가져오기, ARGB 표시 선택(ARGB, ABGR, RGBA, BGRA)

[CSCDropperDlg]
- create()으로 동적 생성? CSCShapeDlg를 사용해야 깔끔한 원 모양의 윈도우 표시될듯.(CreateEllipticRgn은 깔끔하지 않음)
- dropper를 클릭하면 picker는 숨기고 캡처 후 해당 이미지를 dropper에게 전달
- dropper는 현재 커서 중심의 m x m 크기의 이미지를 원형 png 이미지로 그린 후 이를 렌더한다.
