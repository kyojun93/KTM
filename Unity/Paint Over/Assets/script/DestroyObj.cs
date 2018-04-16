using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class DestroyObj : MonoBehaviour {

    public float m_destroyTime = 1.0f;
    private float m_elapsedTime = 0.0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        m_elapsedTime += Time.deltaTime;

        if (m_elapsedTime > m_destroyTime)
        {
            Destroy(gameObject);
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }
	}
}
