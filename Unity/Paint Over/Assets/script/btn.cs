using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class btn : MonoBehaviour {
    public AudioClip m_JumpSound;
    public AudioSource m_CatAudio;
    public Rigidbody2D m_rigidbody;
    public Animator m_animator;
    public GameObject m_Menu;
   
    public void Reset()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
    public void Home()
    {
        SceneManager.LoadScene("Menu");
    }
    public void Jump()
    {
        if (!(m_rigidbody.velocity.y < 0 || m_rigidbody.velocity.y > 0))
        {
            m_CatAudio.PlayOneShot(m_JumpSound);
            m_animator.SetTrigger("jump");
            m_rigidbody.AddForce(transform.up * 300);

        }
    }
    public void Level(bool b)
    {
        m_Menu.SetActive(b);
    }
}
