; ��������� �� ���� ������������� ���������� HD44780 � ������������������� ��������� (���������� ������)
; ���������� ��������� �� ������ "��������". ���� ����� 2 ������ ���������� (���� � ����� ���� + ���� � �������� ����)
; ��� ��������� �� ���� ���������� ������ ("�������") �������� ������ ���� � �������� ��������� ����
; �� ������ ���� ������ � ��������� ���������� �� �������/����������� ��������

include	hardware_profile.inc
include	Macro.h	

#define	USE_STATIC_CURSOR		0				; ������ �������� ������ � ����� 1-� ������
#define	USE_MOVING_CURSOR		1				; ������������ ������������ ������ (�������� �������� ������������� ���� � ������ ��������)
#define	USE_TOP_LAST_CURSOR		1				; ������������ ����������� "������ ����� ������ ������" � "��������� ����� ������ �����" (�������� �������� ������������� ���� � ������ ��������)
#define	USE_RBIE				1				; ������������ ���������� �� ��������� ��������� PORTB ��� ��������� ������ (��������� ������������ ���)
#define	USE_MENU_ACTION			0				; ������������ ����������� ������� �������� ��� ����� � ����� ���� (�������� ������ ��������)

if	USE_MENU_ACTION	
#define	actions_menu_flags		b'00000000'		; ������������ ��� - ���� �������� ��� ����� � ���� ����� ���� (�� ������ ��������� ���������� �������� !!!)
endif

#define	UP						PORTB,4
#define	DOWN					PORTB,5
#define	ENTER					PORTB,6
#define	EXIT					PORTB,7

#define	Press_UP				flags,0
#define	Press_DOWN				flags,1
#define	Press_EXIT				flags,2
#define	Press_ENTER				flags,3	

#define	EXIT_DELAY				.20				; ���������� ������� ������, �� ���������� � ���������� ������� (* 0,8 ���)

#define	ZASTAVKA_FIRST_STRING	"  MicroMenuLib"
#define	ZASTAVKA_SECOND_STRING	"  ver 1.0 beta"

#define	ACTION_COMPLETE_STRING	"Action Complete!"

#define	NUM_OF_MAIN_MENU_PUNKTS	.5				; ���������� ������� ����, �� 8 (����� � ������, �� �������� ��� ����� � ���� �������� ������ ��� ������ 8 �������) 

#define	MENU_NAME_1				"1.Menu_1"
#define	MENU_NAME_2				"2.Menu_2"
#define	MENU_NAME_3				"3.Menu_3"
#define	MENU_NAME_4				"4.Menu_4"
#define	MENU_NAME_5				"5.Menu_5"	

#define	NUM_OF_SUBMENU_PUNKTS_1	.3				; ���������� ���������� ������� ������ ���� (� ������ �� 64, �� ������ 8 �� �����������, ������ � ����������� �� �������)
												; �� �������� �������� ���������� ��� ������� �������� !!!
#define	MENU_SUBMENU_NAME_1_1	"1.1.SubMenu"
#define	MENU_SUBMENU_NAME_1_2	"1.2.SubMenu"
#define	MENU_SUBMENU_NAME_1_3	"1.3.SubMenu"

#define	NUM_OF_SUBMENU_PUNKTS_2	.3

#define	MENU_SUBMENU_NAME_2_1	"2.1.SubMenu"
#define	MENU_SUBMENU_NAME_2_2	"2.2.SubMenu"
#define	MENU_SUBMENU_NAME_2_3	"2.3.SubMenu"
				
#define	NUM_OF_SUBMENU_PUNKTS_3	.3

#define	MENU_SUBMENU_NAME_3_1	"3.1.SubMenu"
#define	MENU_SUBMENU_NAME_3_2	"3.2.SubMenu"
#define	MENU_SUBMENU_NAME_3_3	"3.3.SubMenu"

#define	NUM_OF_SUBMENU_PUNKTS_4	.3

#define	MENU_SUBMENU_NAME_4_1	"4.1.SubMenu"
#define	MENU_SUBMENU_NAME_4_2	"4.2.SubMenu"
#define	MENU_SUBMENU_NAME_4_3	"4.3.SubMenu"

#define	NUM_OF_SUBMENU_PUNKTS_5	.3

#define	MENU_SUBMENU_NAME_5_1	"5.1.SubMenu"
#define	MENU_SUBMENU_NAME_5_2	"5.2.SubMenu"
#define	MENU_SUBMENU_NAME_5_3	"5.3.SubMenu"

;================================================================================================================
Create_Menu_Names	macro				; ������, ������� ����� ���� ������� ����
					local	a=1
					while	a<NUM_OF_MAIN_MENU_PUNKTS+1
						Menu_#v(a)
						mod_PCL	symbol_pointer
						dt		MENU_NAME_#v(a),0
						a+=1
					endw
					endm
;================================================================================================================
retlw_num_of_submenu_punkts	macro		; ������, ���������� ���������� ������� ������� �������
							mod_PCL	index_menu
							local	a=1
							while	a<NUM_OF_MAIN_MENU_PUNKTS+1
								retlw	NUM_OF_SUBMENU_PUNKTS_#v(a)
								a+=1
							endw
							endm
;================================================================================================================
goto_Punkt_Menu	macro					; ������, ������� �������� �� ��� ������ ����
				mod_PCL	index_menu
				local	a=1
				while	a<NUM_OF_MAIN_MENU_PUNKTS+1
					goto	Menu_#v(a)
					a+=1
				endw
				endm
;================================================================================================================
goto_Punkt_Submenu	macro				; ������, ������� �������� �� ����� ���� ���������� ����
					mod_PCL	index_menu				
					local	c=1
					while	c<NUM_OF_MAIN_MENU_PUNKTS+1
						goto	Menu_#v(c)_Table
						c+=1
					endw
					local	d=1
					local	a
					while		d<NUM_OF_MAIN_MENU_PUNKTS+1
						a=1	
						Menu_#v(d)_Table
						mod_PCL	index_submenu
						while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
							goto	Menu_#v(d)_Submenu_#v(a)
							a+=1
						endw
						d+=1
					endw	
					endm
;================================================================================================================
goto_Punkt_Submenu_action	macro		; ������, ������� �������� �� �������� ���� ���������� ����
							mod_PCL	index_menu				
							local	c=1
							while	c<NUM_OF_MAIN_MENU_PUNKTS+1
								goto	Menu_#v(c)_Table_action
								c+=1
							endw
							local	d=1
							local	a
							while		d<NUM_OF_MAIN_MENU_PUNKTS+1
								a=1	
								Menu_#v(d)_Table_action
								mod_PCL	index_submenu
								while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
									goto	Menu_#v(d)_Submenu_#v(a)_action
									a+=1
								endw
								d+=1
							endw
							endm
;================================================================================================================
Create_Submenu_Names	macro				; ������, ������� ����� ���� ���������� ����
; � ���������, ������-�� �� ���������� ��������� ����� ���� ���������� ���� � �����, ������� ���������� �������� ������ ������� ���, ������� ���� ������� ����
; ��������, ���� ���������� ������� � ���� ��������� 8, ������ �������� ���
						local	d=1
;-----------------------------------------------------------------------------------------------------------
; ��������� 1 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_1_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 2 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_2_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 3 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_3_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 4 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_4_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 5 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_5_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 6 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_5_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 7 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_5_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
; ��������� 8 ������ ����
;-----------------------------------------------------------------------------------------------------------
						if		d<NUM_OF_MAIN_MENU_PUNKTS+1
							local	a=1	
							while	a<NUM_OF_SUBMENU_PUNKTS_#v(d)+1
								Menu_#v(d)_Submenu_#v(a)
								mod_PCL	symbol_pointer
								dt		MENU_SUBMENU_NAME_5_#v(a),0
								a+=1
							endw
							d+=1
						endif
;-----------------------------------------------------------------------------------------------------------
						endm
;================================================================================================================
if	USE_MENU_ACTION	
goto_Menu_action	macro		; ������, ������� �������� �� �������� ���� ������� ���� (���� �������� ��������������� �����)
					mod_PCL	index_menu				
					local	a=1
					while	a<NUM_OF_MAIN_MENU_PUNKTS+1
						goto	Menu_#v(a)_action
						a+=1
					endw
					endm
endif