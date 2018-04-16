using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LodingChange : MonoBehaviour {
    private float m_time = 3.0f;
    private float m_starttime = 0.0f;
    GameData Game;
	// Use this for initialization
	void Start () {
        
    }
	
	// Update is called once per frame
	void Update () {
        m_starttime += Time.deltaTime;
        if(m_starttime > m_time)
        {
            SceneManager.LoadScene("Menu");
        }
	}
}
