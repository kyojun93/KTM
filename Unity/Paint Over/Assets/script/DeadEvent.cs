using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeadEvent : MonoBehaviour {
    private List<Vector3> m_pathList = new List<Vector3>();
    private int m_index = 0;
    private float m_elapsedTime = 0;
    private cat m_cat;
    private Vector3 startPosition;
    private Vector3 localScale = new Vector3( 1.5f, 1.5f, 1.5f );
    private Vector3 targetScale= new Vector3(5.5f, 5.5f, 5.5f);
    private Vector3 targetPos = new Vector3(0, -3, 0);
    private float rotSpeed = 360;

    private int m_deadEventIndex = 0;


    private void DisplayCoordinatesSystem()
    {
        m_cat = GameObject.FindGameObjectWithTag("Player").GetComponent<cat>();

    }


    private void Init()
    {
        m_cat = GameObject.FindGameObjectWithTag("Player").GetComponent<cat>();
        m_cat.Stop();
        m_pathList.Add(Camera.main.ScreenToWorldPoint(new Vector3(Screen.width, Screen.height * 0.5f, 10)));

        m_pathList.Add(Camera.main.ScreenToWorldPoint(new Vector3(Screen.width * 0.5f, Screen.height, 10)));

        m_pathList.Add(Camera.main.ScreenToWorldPoint(new Vector3(Screen.width / 2, Screen.height / 2, 10)));
    }

    // Use this for initialization
    private void Start () {
        Init();
        startPosition = m_cat.transform.position;
       
    }

    private void Rotate()
    {
        rotSpeed += Time.deltaTime * 10;

        m_cat.transform.Rotate(0, 0, rotSpeed);

        if (m_index > 2)
            return;

        if (m_index == 2)
            m_cat.transform.localScale = Vector3.Lerp(localScale, targetScale, m_elapsedTime);

        m_cat.transform.position = Vector3.Lerp(startPosition, m_pathList[m_index], m_elapsedTime);


        if (m_elapsedTime > 1)
        {
            m_elapsedTime = 0;

            ++m_index;
            startPosition = m_cat.transform.position;

            if (m_index > 2)
            {
                ++m_deadEventIndex;

                Instantiate<GameObject>(Resources.Load<GameObject>("prefab/ScreenCrack"));
            }
        }
    }

    private void Translate()
    {
        m_cat.transform.position = Vector3.Slerp(startPosition, targetPos, m_elapsedTime);
        m_cat.transform.localScale = Vector3.Slerp( targetScale, localScale, m_elapsedTime);
        if ( m_elapsedTime >= 0.5f )
        {
            m_elapsedTime = 0;
            
            Destroy(gameObject);
        }
    }

    // Update is called once per frame
    private void Update () {
        m_elapsedTime += Time.deltaTime;

        if (m_deadEventIndex == 0)
        {
            Rotate();
        }
        else
        {
            Translate();
        }
    }


}
