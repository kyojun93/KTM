using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class JoyPad : MonoBehaviour {
    public GameObject Cat;
    private Rigidbody2D m_rigidbody;
    private Vector3 m_charDir = Vector3.zero;
    private Animator m_animator;
    // 공개
    public Transform Stick;         // 조이스틱.
    private Vector3 m_vector3= new Vector3(1,1,1);
    // 비공개
    private Vector3 StickFirstPos;  // 조이스틱의 처음 위치.
    private Vector3 JoyVec;         // 조이스틱의 벡터(방향)
    private float Radius;// 조이스틱 배경의 반 지름.
    private bool isMove = false;
    public void Start()
    {
        Radius = GetComponent<RectTransform>().sizeDelta.y * 0.5f;
        StickFirstPos = Stick.transform.position;
        // 캔버스 크기에대한 반지름 조절.
        float Can = transform.parent.GetComponent<RectTransform>().localScale.x;
        Radius *= Can;
        isMove = false;
    }
    private void FixedUpdate()
    {
        Transform tf = Cat.GetComponent<Transform>();
        m_rigidbody = Cat.GetComponent<Rigidbody2D>();
        m_animator = Cat.GetComponent<Animator>();
        if (isMove)
        {
            m_charDir = m_rigidbody.velocity;
            if (JoyVec.x < 0)
            {
                m_charDir.x = -2;
                m_vector3.x = -1;
            }
            else if (JoyVec.x > 0)
            {
                m_charDir.x = 2;
                m_vector3.x = 1;
            }
            tf.localScale = m_vector3;
            m_rigidbody.velocity = m_charDir;
            Debug.Log(JoyVec + " " + m_rigidbody.velocity);
        }
    }
    public void Drag(BaseEventData _Data)
    {
        PointerEventData Data = _Data as PointerEventData;
        Vector3 Pos = Data.position;
        // 조이스틱을 이동시킬 방향을 구함.(오른쪽,왼쪽,위,아래)
        JoyVec = (Pos - StickFirstPos).normalized;

        // 조이스틱의 처음 위치와 현재 내가 터치하고있는 위치의 거리를 구한다.
        float Dis = Vector3.Distance(Pos, StickFirstPos);

        // 거리가 반지름보다 작으면 조이스틱을 현재 터치하고 있는곳으로 이동. 
        if (Dis < Radius)
            Stick.position = StickFirstPos + JoyVec * Dis;
        // 거리가 반지름보다 커지면 조이스틱을 반지름의 크기만큼만 이동.
        else
            Stick.position = StickFirstPos + JoyVec * Radius;
        m_animator.SetInteger("state", (int)1);
        isMove = true;
       
    }
    // 드래그 끝.
    public void DragEnd()
    {
        Stick.position = StickFirstPos; // 스틱을 원래의 위치로.
        JoyVec = Vector3.zero;          // 방향을 0으로.
        m_charDir = m_rigidbody.velocity;
        m_charDir.x = 0;
        m_rigidbody.velocity = m_charDir;

        m_animator.SetInteger("state", 0);
        isMove = false;
    }
}
